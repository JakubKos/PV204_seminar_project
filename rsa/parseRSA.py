#!/usr/bin/python3.6
import subprocess
import csv

INI_STATE = 0
N_STATE = 1
P_STATE = 2
Q_STATE = 3
D_STATE = 4

TYPE = 512

with open(f"rsatimes-{TYPE}.csv", "r") as inf, open(f"rsatimes-{TYPE}-fin.csv", "w") as outf:
    reader = csv.reader(inf, delimiter=';')
    writer = csv.writer(outf, delimiter=';')

    for x in range(1, 1000001):
        out = subprocess.check_output(["openssl", "rsa", "-inform", "DER", "-in", f"keys/{TYPE}/{x:06}.der", "-text"]).decode().splitlines()
        state = INI_STATE
        n = ""
        p = ""
        q = ""
        d = ""
        for line in out:
            if line == "modulus:":
                state = N_STATE
                continue
            elif line == "prime1:":
                state = P_STATE
                continue
            elif line == "prime2:":
                state = Q_STATE
                continue
            elif line == "privateExponent:":
                state = D_STATE
                continue
            elif line[0] != ' ':
                state = INI_STATE
                continue

            if state == N_STATE:
                n += line.strip()
            elif state == P_STATE:
                p += line.strip()
            elif state == Q_STATE:
                q += line.strip()
            elif state == D_STATE:
                d += line.strip()

        row = next(reader)
        row[1] = n
        row[3] = p
        row[4] = q
        row[5] = d
        writer.writerow(row + [''])
