import subprocess
import csv

INI_STATE = 0
PRI_STATE = 1
PUB_STATE = 2

with open("ectimes.csv", "r") as inf, open("eckeys.csv", "w") as outf:
    reader = csv.reader(inf, delimiter=';')
    writer = csv.writer(outf, delimiter=';')

    for x in range(1000000):
        out = subprocess.check_output(["openssl", "ec", "-inform", "DER", "-in", f"eckeys/{x:06}.der", "-text"]).decode().splitlines()
        state = INI_STATE
        pri = ""
        pub = ""
        for line in out:
            if line == "priv:":
                state = PRI_STATE
                continue
            elif line == "pub:":
                state = PUB_STATE
                continue
            elif line[0] != ' ':
                state = INI_STATE
                continue

            if state == PRI_STATE:
                pri += line.strip()
            elif state == 2:
                pub += line.strip()

        # parsed
        row = next(reader)
        row[1] = pub.replace(":", "")
        row[2] = pri.replace(":", "")
        writer.writerow(row + [''])
