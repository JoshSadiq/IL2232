'''
Hengzhen Yuan wrote on 2024.1.10
IL2232 project Time series analysis
'''

import torch
import torchvision
from torchvision import datasets, transforms
import torch.utils.data
import numpy as np
# network structure
import torch.nn as nn
import torch.nn.functional as F
import csv
###########################设置全局变量###################################

num_time_steps = 50
input_size = 1
hidden_size = 16
output_size = 1
num_layers = 1
num_directions = 1
lr=0.01
class Net(nn.Module):

    def __init__(self, input_size, hidden_size, num_layers):
        super(Net, self).__init__()

        self.rnn = nn.RNN(
            input_size=input_size,
            hidden_size=hidden_size,
            num_layers=num_layers,
            batch_first=True,
        )
        for p in self.rnn.parameters():
          nn.init.normal_(p, mean=0.0, std=0.001)

        self.linear = nn.Linear(hidden_size, output_size)

    def forward(self, x, hidden_prev):

       out, hidden_prev = self.rnn(x, hidden_prev)
       # [b, seq, h]
       out = out.view(-1, hidden_size)
       out = self.linear(out)#[seq,h] => [seq,3]
       out = out.unsqueeze(dim=0)  # => [1,seq,3]
       return out, hidden_prev


if __name__ == "__main__":
    net = Net(input_size, hidden_size, num_layers)
    net.load_state_dict(torch.load('./model/net_RNN2.pt'))

    ## weight output
    f = open("./model/weights_RNN2.txt", "a", newline='')
    for layerNum, layer in enumerate(net.children()):
        # if layerNum <= 2:
        #     continue
        print(layerNum, layer)
        if isinstance(layer, nn.RNN):

            print(layer.all_weights)
            import torch




            weight_ih_l = []
            weight_hh_l = []
            bias_ih_l = []
            bias_hh_l = []


            # # 循环遍历 all_weights，并将张量分配到相应的变量中
            # for k in range(0, 4, 1):  # 以步长 2 遍历，因为每个权重和偏置都是成对的
            #     # weight_ih_l[k]
            #     if k == 0:
            #         weight_ih = layer.all_weights[k].data.view(hidden_size, input_size)
            #     else:
            #         weight_ih = layer.all_weights[k].data.view(hidden_size, num_directions * hidden_size)
            #     weight_ih_l.append(weight_ih)

                # # weight_hh_l[k]
                # weight_hh = layer.all_weights[k + 1][0].view(hidden_size, hidden_size)
                # weight_hh_l.append(weight_hh)
                #
                # # bias_ih_l[k]
                # bias_ih = layer.all_weights[k + 2][0].view(hidden_size)
                # bias_ih_l.append(bias_ih)
                #
                # # bias_hh_l[k]
                # bias_hh =layer.all_weights[k + 3][0].view(hidden_size)
                # bias_hh_l.append(bias_hh)

            # 打印结果


            # w = layer.weight.data.detach().numpy()
            # b = layer.bias.data.detach().numpy()
            # n = b.shape[0]
            # w = w.reshape((n, -1))
            # b = b.reshape((n, -1))
            # w = np.concatenate((w, b), axis=1)
            # csv.writer(f, delimiter=' ').writerows(w)
        elif isinstance(layer, nn.Linear):
            print(layer.weight)
            print(layer.bias)
            w = layer.weight.data.detach().numpy()
            b = layer.bias.data.detach().numpy()
            n = b.shape[0]
            b = b.reshape((n, -1))
            w = np.concatenate((w, b), axis=1)
            csv.writer(f, delimiter=' ').writerows(w)

    f.close()
