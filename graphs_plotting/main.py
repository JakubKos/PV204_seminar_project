import matplotlib.pyplot as plt
import csv


def show_graph(values, label, bins, rang):
    """
    Plot histogram.
    :param values: values to be plotted
    :param label: x-label
    :param bins: level of granularity
    :param rang: plotted range
    :return: None
    """
    plt.hist(values, bins=bins, range=rang)
    plt.xlabel(label)
    plt.show()


def prepare_ecc_priv_msb_graph(path):
    """
    Extrac MSB from priv key given in CSV.
    :param path: path to the CSV file
    :return: extracted data
    """
    msb_private_ecc = []

    # open csv and parse desired values to array
    with open(path, 'r') as csvfile:
        plots = csv.reader(csvfile, delimiter=';')
        for row in plots:
            # parse only MSB from priv key and convert value to int.
            msb_private_ecc.append(int(row[2].replace(':', '')[0:2], 16))

    return msb_private_ecc


def prepare_ecc_priv_lsb_graph(path):
    """
    Extrac LSB from priv key given in CSV.
    :param path: path to the CSV file
    :return: extracted data
    """
    lsb_private_ecc = []

    # open csv and parse desired values to array
    with open(path, 'r') as csvfile:
        plots = csv.reader(csvfile, delimiter=';')
        for row in plots:
            # parse only LSB from priv key and convert value to int.
            lsb_private_ecc.append(int(row[2].replace(':', '')[-2:], 16))

    return lsb_private_ecc


def prepare_ecc_priv_times(path):
    """
    Extrac time from priv key given in CSV.
    :param path: path to the CSV file
    :return: extracted data
    """
    times = []

    # open csv and parse desired values to array
    with open(path, 'r') as csvfile:
        plots = csv.reader(csvfile, delimiter=';')
        for row in plots:
            # parse only LSB from priv key and convert value to int.
            times.append(int(row[3], 10)/1000)

    return times

if __name__ == '__main__':
    pass
#    show_graph(prepare_ecc_priv_times('/home/kubo/Documents/Magisterske_studium/PV204/zing/eckeys.csv'), 'Time to generate key (microseconds)', 300, (840, 990))
#    show_graph(prepare_ecc_priv_lsb_graph('/home/kubo/Documents/Magisterske_studium/PV204/zing/eckeys.csv'), 'LSB of priv key', None, None)
#    show_graph(prepare_ecc_priv_msb_graph('/home/kubo/Documents/Magisterske_studium/PV204/zing/eckeys.csv'), 'MSB of priv key', 500, None)