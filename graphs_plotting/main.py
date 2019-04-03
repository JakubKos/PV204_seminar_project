import matplotlib.pyplot as plt
import csv
import numpy as np
import os


def show_graph(path, bins, ecc):
    """
    Plot histogram.
    :param values: values to be plotted
    :param label: x-label
    :param bins: level of granularity
    :param rang: plotted range
    :return: None
    """
    values = []

    with open(path, 'r') as file:
        for line in file:
            values.append(int(line))

    values.sort()
    values = values[5:-5]

    labelX = 'Time to evaluate function call (microseconds)'
    labelY = 'Number of occurences'
    if ecc:
        plotName = get_function_name_ecc(path) + get_prng(path) + get_data(path)
    else:
        plotName = get_function_name(path) + get_prng(path) + get_data(path)

    plt.hist(values, bins=bins, range=(values[0], values[-1]), edgecolor='black')
    plt.xlabel(labelX)
    plt.ylabel(labelY)
    plt.title(plotName)
    plt.xticks()
    print('Saving graph ' + os.path.splitext(path)[0])
    plt.savefig(os.path.splitext(path)[0] + '.png', bbox_inches='tight')
    plt.close()


def get_function_name_ecc(argument):
    if argument.endswith("dec.txt"):
        return 'wc_ecc_decrypt()'

    if argument.endswith("enc.txt"):
        return 'wc_ecc_encrypt()'

    if argument.endswith("sig.txt"):
        return 'wc_ecc_sign_hash()'

    if argument.endswith("mak.txt"):
        return 'wc_ecc_make_key_ex()'


def get_function_name_rsa(argument):
    if argument.endswith("dec.txt"):
        return 'wc_RsaPrivateDecrypt_ex()'

    if argument.endswith("enc.txt"):
        return 'wc_RsaPublicEncrypt_ex()'

    if argument.endswith("sign.txt"):
        return 'wc_RsaSSL_Sign'

    if argument.endswith("mak.txt"):
        return 'wc_ecc_make_key_ex()'


def get_prng(argument):
    if 'prng0' in argument:
        return ' • PRNG: default generator'

    if 'prng1' in argument:
        return ' • PRNG: all ones'

    if 'prng2' in argument:
        return ' • PRNG: repeating pattern 0x00FF'

    if 'prng3' in argument:
        return ' • PRNG: repeating pattern 0xAAAA (101010)'

    if 'prng4' in argument:
        return ' • PRNG: repeating pattern 0x8000 (one 1 31*0 after that)'

    if 'prng5' in argument:
        return ' • PRNG: all 0, lowest bit 1'

    if 'prng6' in argument:
        return ' • PRNG: all 0, highest bit 1'


def get_data(argument):
    if 'data0' in argument:
        return ' • DATA: 1 to 255'

    if 'data1' in argument:
        return ' • DATA: all ones'

    if 'data2' in argument:
        return ' • DATA: repeating pattern 0x00FF'

    if 'data3' in argument:
        return ' • DATA: repeating pattern 0xAAAA (101010)'

    if 'data4' in argument:
        return ' • DATA: repeating pattern 0x8000 (one 1 31*0 after that)'

    if 'data5' in argument:
        return ' • DATA: all 0'


if __name__ == '__main__':

    directory_ec = '/home/kubo/Documents/Magisterske_studium/PV204/project/PV204_seminar_project/ec/measurement/'
    directory_rsa = ''
    for file in os.listdir(directory):
        if file.endswith('.txt'):
            # show_graph(directory_ec + file, 35, True)
            show_graph(directory_rsa + file, 35, False)
