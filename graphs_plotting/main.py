import matplotlib.pyplot as plt
import csv

# Plotting

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

# ECC part

def prepare_ecc_priv_msb_graph(path):
    """
    Extract MSB from priv key given in CSV.
    :param path: path to the CSV file
    :return: extracted data
    """
    msb_private_ecc = []

    # open csv and parse desired values to array
    with open(path, 'r') as csvfile:
        plots = csv.reader(csvfile, delimiter=';')
        for row in plots:
            msb_private_ecc.append(int(row[2].replace(':', '')[0:2], 16))

    return msb_private_ecc


def prepare_ecc_priv_lsb_graph(path):
    """
    Extract LSB from priv key given in CSV.
    :param path: path to the CSV file
    :return: extracted data
    """
    lsb_private_ecc = []

    # open csv and parse desired values to array
    with open(path, 'r') as csvfile:
        plots = csv.reader(csvfile, delimiter=';')
        for row in plots:
            lsb_private_ecc.append(int(row[2].replace(':', '')[-2:], 16))

    return lsb_private_ecc


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

# RSA part

def prepare_p_prime_msb(path):
    """
    Extract MSB from P prime given in CSV.
    :param path: path to the CSV file
    :return: extracted data
    """
    msb_p_prime = []

    # open csv and parse desired values to array
    with open(path, 'r') as csvfile:
        plots = csv.reader(csvfile, delimiter=';')
        for row in plots:
            msb_p_prime.append(int(row[3].replace(':', '')[2:4], 16))

    return msb_p_prime


def prepare_q_prime_msb(path):
    """
    Extract MSB from Q prime given in CSV.
    :param path: path to the CSV file
    :return: extracted data
    """
    msb_q_prime = []

    # open csv and parse desired values to array
    with open(path, 'r') as csvfile:
        plots = csv.reader(csvfile, delimiter=';')
        for row in plots:
            msb_q_prime.append(int(row[4].replace(':', '')[2:4], 16))

    return msb_q_prime


def prepare_p_prime_lsb(path):
    """
    Extract LSB from P prime given in CSV.
    :param path: path to the CSV file
    :return: extracted data
    """
    lsb_p_prime = []

    # open csv and parse desired values to array
    with open(path, 'r') as csvfile:
        plots = csv.reader(csvfile, delimiter=';')
        for row in plots:
            lsb_p_prime.append(int(row[3].replace(':', '')[-2:], 16))

    return lsb_p_prime


def prepare_q_prime_lsb(path):
    """
    Extract LSB from Q prime given in CSV.
    :param path: path to the CSV file
    :return: extracted data
    """
    lsb_q_prime = []

    # open csv and parse desired values to array
    with open(path, 'r') as csvfile:
        plots = csv.reader(csvfile, delimiter=';')
        for row in plots:
            lsb_q_prime.append(int(row[4].replace(':', '')[-2:], 16))

    return lsb_q_prime


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
    # ECC MSB priv
    # show_graph(prepare_ecc_priv_msb_graph('/home/kubo/Documents/Magisterske_studium/PV204/zing/eckeys.csv'), 'MSB of priv key', 500, None)
    # show_graph(prepare_ecc_priv_msb_graph('/home/kubo/Documents/Magisterske_studium/PV204/zing/eckeys.csv'), 'MSB of priv key', None, None)

    # ECC LSB priv
    # show_graph(prepare_ecc_priv_lsb_graph('/home/kubo/Documents/Magisterske_studium/PV204/zing/eckeys.csv'), 'LSB of priv key', 500, None)
    # show_graph(prepare_ecc_priv_lsb_graph('/home/kubo/Documents/Magisterske_studium/PV204/zing/eckeys.csv'), 'LSB of priv key', None, None)

    # ECC TIMES
    # show_graph(prepare_ecc_priv_times('/home/kubo/Documents/Magisterske_studium/PV204/zing/eckeys.csv'), 'Time to generate key (microseconds)', None, None)
    # show_graph(prepare_ecc_priv_times('/home/kubo/Documents/Magisterske_studium/PV204/zing/eckeys.csv'), 'Time to generate key (microseconds)', 500, None)
    # show_graph(prepare_ecc_priv_times('/home/kubo/Documents/Magisterske_studium/PV204/zing/eckeys.csv'), 'Time to generate key (microseconds)', None, (840, 990))
    # show_graph(prepare_ecc_priv_times('/home/kubo/Documents/Magisterske_studium/PV204/zing/eckeys.csv'), 'Time to generate key (microseconds)', 300, (840, 990))

    # -----------------------------------------------------------------------------------------------------------------

    # RSA 512 P prime MSB
    # show_graph(prepare_p_prime_msb('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-512-fin.csv'), 'MSB P', 250, None)
    # show_graph(prepare_p_prime_msb('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-512-fin.csv'), 'MSB P', None, None)

    # RSA 512 Q prime MSB
    # show_graph(prepare_q_prime_msb('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-512-fin.csv'), 'MSB Q', 250, None)
    # show_graph(prepare_q_prime_msb('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-512-fin.csv'), 'MSB Q', None, None)

    # RSA 512 P prime LSB
    # show_graph(prepare_p_prime_lsb('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-512-fin.csv'), 'LSB P', 250, None)
    # show_graph(prepare_p_prime_lsb('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-512-fin.csv'), 'LSB P', None, None)

    # RSA 512 Q prime LSB
    # show_graph(prepare_q_prime_lsb('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-512-fin.csv'), 'LSB Q', 250, None)
    # show_graph(prepare_q_prime_lsb('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-512-fin.csv'), 'LSB Q', None, None)

    # RSA 512 times
    # show_graph(prepare_rsa_times('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-512-fin.csv'), 'Time to generate (miliseconds)', None, None)
    # show_graph(prepare_rsa_times('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-512-fin.csv'), 'Time to generate (miliseconds)', 500, None)
    # show_graph(prepare_rsa_times('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-512-fin.csv'), 'Time to generate (miliseconds)', None, (0,45))
    # show_graph(prepare_rsa_times('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-512-fin.csv'), 'Time to generate (miliseconds)', 300, (0,45))

    # -----------------------------------------------------------------------------------------------------------------

    # RSA 1024 P prime MSB
    # show_graph(prepare_p_prime_msb('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-1024-fin.csv'), 'MSB P', 250, None)
    # show_graph(prepare_p_prime_msb('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-1024-fin.csv'), 'MSB P', None, None)

    # RSA 1024 Q prime MSB
    # show_graph(prepare_q_prime_msb('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-1024-fin.csv'), 'MSB Q', 250, None)
    # show_graph(prepare_q_prime_msb('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-1024-fin.csv'), 'MSB Q', None, None)

    # RSA 1024 P prime LSB
    # show_graph(prepare_p_prime_lsb('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-1024-fin.csv'), 'LSB P', 250, None)
    # show_graph(prepare_p_prime_lsb('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-1024-fin.csv'), 'LSB P', None, None)

    # RSA 1024 Q prime LSB
    # show_graph(prepare_q_prime_lsb('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-1024-fin.csv'), 'LSB Q', 250, None)
    # show_graph(prepare_q_prime_lsb('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-1024-fin.csv'), 'LSB Q', None, None)

    # RSA 1024 times
    # show_graph(prepare_rsa_times('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-1024-fin.csv'), 'Time to generate (miliseconds)', None, None)
    # show_graph(prepare_rsa_times('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-1024-fin.csv'), 'Time to generate (miliseconds)', 500, None)

    # -----------------------------------------------------------------------------------------------------------------

    # RSA 2048 P prime MSB
    # show_graph(prepare_p_prime_msb('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-2048-fin.csv'), 'MSB P', 250, None)
    # show_graph(prepare_p_prime_msb('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-2048-fin.csv'), 'MSB P', None, None)

    # RSA 2048 Q prime MSB
    # show_graph(prepare_q_prime_msb('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-2048-fin.csv'), 'MSB Q', 250, None)
    # show_graph(prepare_q_prime_msb('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-2048-fin.csv'), 'MSB Q', None, None)

    # RSA 2048 P prime LSB
    # show_graph(prepare_p_prime_lsb('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-2048-fin.csv'), 'LSB P', 250, None)
    # show_graph(prepare_p_prime_lsb('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-2048-fin.csv'), 'LSB P', None, None)

    # RSA 2048 Q prime LSB
    # show_graph(prepare_q_prime_lsb('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-2048-fin.csv'), 'LSB Q', 250, None)
    # show_graph(prepare_q_prime_lsb('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-2048-fin.csv'), 'LSB Q', None, None)

    # RSA 2048 times
    # show_graph(prepare_rsa_times('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-2048-fin.csv'), 'Time to generate (miliseconds)', None, None)
    # show_graph(prepare_rsa_times('/home/kubo/Documents/Magisterske_studium/PV204/project/rsatimes/rsatimes-2048-fin.csv'), 'Time to generate (miliseconds)', 500, None)
    pass

