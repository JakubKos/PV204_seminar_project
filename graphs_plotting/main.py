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


def prepare_data(path, start_index, stop_index, row_index):
    """
        Extract data from from given CSV.
        :param row_index: row index of data which we want to parse
        :param stop_index: start index of data which we want to parse
        :param start_index:  end index of data which we want to parse
        :param path: path to the CSV file
        :return: extracted data
        """
    data = []

    # open csv and parse desired values to array
    with open(path, 'r') as csvfile:
        plots = csv.reader(csvfile, delimiter=';')
        for row in plots:
            data.append(int(row[row_index].replace(':', '')[start_index:stop_index], 16))

    return data


def prepare_ecc_priv_times(path):
    """
    Extract time from priv key given in CSV.
    :param path: path to the CSV file
    :return: extracted data
    """
    times = []

    # open csv and parse desired values to array
    with open(path, 'r') as csvfile:
        plots = csv.reader(csvfile, delimiter=';')
        for row in plots:
            times.append(int(row[3], 10)/1000)

    return times


def prepare_rsa_times(path):
    """
    Extract time from rsa keys given in CSV.
    :param path: path to the CSV file
    :return: extracted data
    """
    times = []

    # open csv and parse desired values to array
    with open(path, 'r') as csvfile:
        plots = csv.reader(csvfile, delimiter=';')
        for row in plots:
            times.append(int(row[6], 10)/1000000)

    return times


if __name__ == '__main__':
    # ECC MSB X
    show_graph(prepare_data('/home/kubo/Documents/Magisterske_studium/PV204/zing/eckeys.csv', 2, 4, 1),
               'MSB of point X', 500, None)
    show_graph(prepare_data('/home/kubo/Documents/Magisterske_studium/PV204/zing/eckeys.csv', 2, 4, 1),
               'MSB of point X', None, None)

    # ECC LSB X
    show_graph(prepare_data('/home/kubo/Documents/Magisterske_studium/PV204/zing/eckeys.csv', 64, 66, 1),
               'LSB of point X', 500, None)
    show_graph(prepare_data('/home/kubo/Documents/Magisterske_studium/PV204/zing/eckeys.csv', 64, 66, 1),
               'LSB of point X', None, None)

    # ECC MSB Y
    show_graph(prepare_data('/home/kubo/Documents/Magisterske_studium/PV204/zing/eckeys.csv', 66, 68, 1),
               'MSB of point Y', 500, None)
    show_graph(prepare_data('/home/kubo/Documents/Magisterske_studium/PV204/zing/eckeys.csv', 66, 68, 1),
               'MSB of point Y', None, None)

    # ECC LSB Y
    show_graph(prepare_data('/home/kubo/Documents/Magisterske_studium/PV204/zing/eckeys.csv', -2, None, 1),
               'LSB of point Y', 500, None)
    show_graph(prepare_data('/home/kubo/Documents/Magisterske_studium/PV204/zing/eckeys.csv', -2, None, 1),
               'LSB of point Y', None, None)

    # ECC MSB k
    show_graph(prepare_data('/home/kubo/Documents/Magisterske_studium/PV204/zing/eckeys.csv', 0, 2, 2),
               'MSB of k', 500, None)
    show_graph(prepare_data('/home/kubo/Documents/Magisterske_studium/PV204/zing/eckeys.csv', 0, 2, 2),
               'MSB of k', None, None)

    # ECC LSB k
    show_graph(prepare_data('/home/kubo/Documents/Magisterske_studium/PV204/zing/eckeys.csv', -2, None, 2),
               'LSB of k', 500, None)
    show_graph(prepare_data('/home/kubo/Documents/Magisterske_studium/PV204/zing/eckeys.csv', -2, None, 2),
               'LSB of k', None, None)

    # ECC TIMES
    show_graph(prepare_ecc_priv_times('/home/kubo/Documents/Magisterske_studium/PV204/zing/eckeys.csv'),
               'Time to generate key (microseconds)', None, None)
    show_graph(prepare_ecc_priv_times('/home/kubo/Documents/Magisterske_studium/PV204/zing/eckeys.csv'),
               'Time to generate key (microseconds)', 500, None)
    show_graph(prepare_ecc_priv_times('/home/kubo/Documents/Magisterske_studium/PV204/zing/eckeys.csv'),
               'Time to generate key (microseconds)', None, (840, 990))
    show_graph(prepare_ecc_priv_times('/home/kubo/Documents/Magisterske_studium/PV204/zing/eckeys.csv'),
               'Time to generate key (microseconds)', 300, (840, 990))

    # -----------------------------------------------------------------------------------------------------------------

    # RSA 512 P prime MSB
    show_graph(prepare_data('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-512-fin.csv', 2, 4, 3), 'MSB P', 250, None)
    show_graph(prepare_data('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-512-fin.csv', 2, 4 ,3), 'MSB P', None, None)

    # RSA 512 Q prime MSB
    show_graph(prepare_data('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-512-fin.csv', 2, 4, 4), 'MSB Q', 250, None)
    show_graph(prepare_data('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-512-fin.csv', 2, 4, 4), 'MSB Q', None, None)

    # RSA 512 P prime LSB
    show_graph(prepare_data('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-512-fin.csv', -2, None, 3), 'LSB P', 250, None)
    show_graph(prepare_data('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-512-fin.csv', -2, None, 3), 'LSB P', None, None)

    # RSA 512 Q prime LSB
    show_graph(prepare_data('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-512-fin.csv', -2, None, 4), 'LSB Q', 250, None)
    show_graph(prepare_data('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-512-fin.csv', -2, None, 4), 'LSB Q', None, None)

    # RSA 512 times
    show_graph(prepare_rsa_times('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-512-fin.csv'), 'Time to generate key (miliseconds)', None, None)
    show_graph(prepare_rsa_times('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-512-fin.csv'), 'Time to generate key (miliseconds)', 500, None)
    show_graph(prepare_rsa_times('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-512-fin.csv'), 'Time to generate key (miliseconds)', None, (0,45))
    show_graph(prepare_rsa_times('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-512-fin.csv'), 'Time to generate key (miliseconds)', 300, (0,45))

    # -----------------------------------------------------------------------------------------------------------------

    # RSA 1024 P prime MSB
    show_graph(prepare_data('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-1024-fin.csv', 2, 4, 3), 'MSB P', 250, None)
    show_graph(prepare_data('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-1024-fin.csv', 2, 4, 3), 'MSB P', None, None)

    # RSA 1024 Q prime MSB
    show_graph(prepare_data('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-1024-fin.csv', 2, 4, 4), 'MSB Q', 250, None)
    show_graph(prepare_data('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-1024-fin.csv', 2, 4, 4), 'MSB Q', None, None)

    # RSA 1024 P prime LSB
    show_graph(prepare_data('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-1024-fin.csv', -2, None, 3), 'LSB P', 250, None)
    show_graph(prepare_data('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-1024-fin.csv', -2, None, 3), 'LSB P', None, None)

    # RSA 1024 Q prime LSB
    show_graph(prepare_data('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-1024-fin.csv', -2, None, 4), 'LSB Q', 250, None)
    show_graph(prepare_data('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-1024-fin.csv', -2, None, 4), 'LSB Q', None, None)

    # RSA 1024 times
    show_graph(prepare_rsa_times('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-1024-fin.csv'), 'Time to generate key (miliseconds)', None, None)
    show_graph(prepare_rsa_times('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-1024-fin.csv'), 'Time to generate key (miliseconds)', 500, None)

    # -----------------------------------------------------------------------------------------------------------------

    # RSA 2048 P prime MSB
    show_graph(prepare_data('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-2048-fin.csv', 2, 4, 3), 'MSB P', 250, None)
    show_graph(prepare_data('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-2048-fin.csv', 2, 4, 3), 'MSB P', None, None)

    # RSA 2048 Q prime MSB
    show_graph(prepare_data('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-2048-fin.csv', 2, 4, 4), 'MSB Q', 250, None)
    show_graph(prepare_data('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-2048-fin.csv', 2, 4, 4), 'MSB Q', None, None)

    # RSA 2048 P prime LSB
    show_graph(prepare_data('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-2048-fin.csv', -2, None, 3), 'LSB P', 250, None)
    show_graph(prepare_data('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-2048-fin.csv', -2, None, 3), 'LSB P', None, None)

    # RSA 2048 Q prime LSB
    show_graph(prepare_data('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-2048-fin.csv', -2, None, 4), 'LSB Q', 250, None)
    show_graph(prepare_data('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-2048-fin.csv', -2, None, 4), 'LSB Q', None, None)

    # RSA 2048 times
    show_graph(prepare_rsa_times('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-2048-fin.csv'), 'Time to generate key (miliseconds)', None, None)
    show_graph(prepare_rsa_times('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-2048-fin.csv'), 'Time to generate key (miliseconds)', 500, None)


