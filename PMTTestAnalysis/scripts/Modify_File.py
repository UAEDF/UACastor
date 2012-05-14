#!/usr/bin/python
import sys
import os

MAXL = 1000000000;
#MAXL = 10;

def seconds( time ):
    sec   = time.split(':')[5]
    min   = time.split(':')[4]
    hour  = time.split(':')[3]
    #print hour, min, sec
    return int(hour)*3600 + int(min)*60 + int(sec)


def ReadFile( FileName ):
    print FileName
    f = open(FileName,"r")
    try:
        ii=0
        for line in f:
            if(ii<MAXL):
                if(ii==0):
                    starttime = line.split()[4]
                    start     = seconds(starttime)
                timestr  = line.split()[4]
                hv    = int(line.split()[9])
                cath  = float(line.split()[14])
                adut  = float(line.split()[16])
                aref  = float(line.split()[17])
                time  = seconds(timestr) - start # seconds from first point - your x coordinate
                led   = int(line.split()[5])
                print '{0:20s}\t{1:8d}\t{2:6d}\t\t{3:10.3e}\t{4:10.4e}\t{5:10.4e}\t{6}'.format(timestr,
                                                                                               time,
                                                                                               hv,
                                                                                               cath,
                                                                                               adut,
                                                                                               aref,
                                                                                               led)
            ii=ii+1
    finally:
        f.close()
    return

if __name__ == "__main__":
    if (len(sys.argv) > 1):
        ReadFile(sys.argv[1]);
    else:
        print "enter name of the file"


