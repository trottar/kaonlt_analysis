#!/usr/bin/env python

import time,sys,os,argparse,atexit,subprocess,math

from collections import namedtuple

import matplotlib.pyplot as plt

from array import array


target = sys.argv[1]
#target = "Carbon"
numRuns = 5
comment="Clean pion cuts"

def getValues() :

    run_num = array('i')          
    HMS_EVENTS = array('f')
    HMS_EVENTSun = array('f')
    SHMS_EVENTS = array('f')
    SHMS_EVENTSun = array('f')
    HMS_track = array('f')                                
    HMS_trackun = array('f')
    HMS_etrack = array('f')                     
    HMS_etrackun = array('f')
    SHMS_track = array('f')                     
    SHMS_trackun = array('f')
    SHMS_hadtrack = array('f')                  
    SHMS_hadtrackun = array('f')
    SHMS_pitrack = array('f')                 
    SHMS_pitrackun = array('f')
    SHMS_Ktrack = array('f')    
    SHMS_Ktrackun = array('f')
    SHMS_ptrack = array('f')    
    SHMS_ptrackun = array('f')
    ACC_EDTM = array('f')
    TRIG1_cut = array('f')
    TRIG3_cut = array('f')
    PS1 = array('f')
    PS3 = array('f')
    TIME = array('f')
    BCM4B = array('f')
    pTRIG1 = array('f')
    pTRIG3 = array('f')
    #comp_time = array('f')      
    #comp_uncer = array('f')     
    #HMS_elec = array('f')       
    #HMS_elecun = array('f')     
    #SHMS_elec = array('f')      
    #SHMS_elecun = array('f')
    SENT_EDTM = array('f')
    
    filename = "yieldVar"
    
    f = open(filename)
    
    for line in f:
        data = line.split()
        #print(str(data))
        if "#" not in line :
            run_num.append(int(data[0]))    
            #print("Run %s" % (run_num))
            HMS_EVENTS.append(float(data[1]))
            HMS_EVENTSun.append(float(data[2]))
            SHMS_EVENTS.append(float(data[3]))
            SHMS_EVENTSun.append(float(data[4]))
            HMS_track.append(float(data[5]))        
            HMS_trackun.append(float(data[6]))
            HMS_etrack.append(float(data[7]))       
            HMS_etrackun.append(float(data[8]))
            #print("HMS etrack %s" % (HMS_etrack))
            SHMS_track.append(float(data[9]))       
            SHMS_trackun.append(float(data[10]))
            SHMS_hadtrack.append(float(data[11]))     
            SHMS_hadtrackun.append(float(data[12]))
            SHMS_pitrack.append(float(data[13]))      
            SHMS_pitrackun.append(float(data[14]))
            SHMS_Ktrack.append(float(data[15]))       
            SHMS_Ktrackun.append(float(data[16]))
            SHMS_ptrack.append(float(data[17]))       
            SHMS_ptrackun.append(float(data[18]))
            ACC_EDTM.append(float(data[19]))
            TRIG1_cut.append(float(data[20]))
            TRIG3_cut.append(float(data[21]))
            PS1.append(float(data[22]))
            PS3.append(float(data[23]))
            TIME.append(float(data[24]))
            #print("TIME %s" % (TIME))
            BCM4B.append(float(data[25]))
            #print("BCM4B %s" % (BCM4B))
            pTRIG1.append(float(data[26]))
            pTRIG3.append(float(data[27]))
            #comp_time = np.append(,len(),float(data[]))  
            #comp_uncer = np.append(,len(),float(data[])) 
            #HMS_elec = np.append(,len(),float(data[]))   
            #HMS_elecun = np.append(,len(),float(data[])) 
            #SHMS_elec = np.append(,len(),float(data[]))  
            #SHMS_elecun = np.append(,len(),float(data[]))
            SENT_EDTM.append(float(data[28]))
            #print("EDTM %s" % (SENT_EDTM))
 
    f.close()

    return[run_num,HMS_EVENTS,HMS_EVENTSun,SHMS_EVENTS,SHMS_EVENTSun,HMS_track,HMS_trackun,HMS_etrack,HMS_etrackun,SHMS_track,SHMS_trackun,SHMS_hadtrack,SHMS_hadtrackun,SHMS_pitrack,SHMS_pitrackun,SHMS_Ktrack,SHMS_Ktrackun,SHMS_ptrack,SHMS_ptrackun,ACC_EDTM,TRIG1_cut,TRIG3_cut,PS1,PS3,TIME,BCM4B,pTRIG1,pTRIG3, SENT_EDTM]


def findVar() :

    [run_num,HMS_EVENTS,HMS_EVENTSun,SHMS_EVENTS,SHMS_EVENTSun,HMS_track,HMS_trackun,HMS_etrack,HMS_etrackun,SHMS_track,SHMS_trackun,SHMS_hadtrack,SHMS_hadtrackun,SHMS_pitrack,SHMS_pitrackun,SHMS_Ktrack,SHMS_Ktrackun,SHMS_ptrack,SHMS_ptrackun,ACC_EDTM,TRIG1_cut,TRIG3_cut,PS1,PS3,TIME,BCM4B,pTRIG1,pTRIG3, SENT_EDTM] = getValues()

    current = array('f',[x/y for x,y in zip(BCM4B,TIME)])
    rate_HMS = array('f',[x/y for x,y in zip(HMS_EVENTS,TIME)])
    rate_SHMS = array('f',[x/y for x,y in zip(SHMS_EVENTS,TIME)])
    cpuLT_uncer = array('f',[math.sqrt(x+y)/(x+y) for x,y in zip(TRIG1_cut,TRIG3_cut)])
    cpuLT_HMS = array('f',[x/((y-z)/p) for x,y,z,p in zip(TRIG3_cut,pTRIG3,SENT_EDTM,PS3)])
    cpuLT_SHMS = array('f',[x/((y-z)/p) for x,y,z,p in zip(TRIG1_cut,pTRIG1,SENT_EDTM,PS1)])
    uncerEvts_HMS = array('f',[math.sqrt(x)/x for x in HMS_EVENTS])
    uncerEvts_SHMS = array('f',[math.sqrt(x)/x for x in SHMS_EVENTS])

    #print("String currents are %s" % (current))

    #for i in range(numRuns) :
        #print("Currents are %0.2f" % (current[i]))

    return[current,rate_HMS,rate_SHMS,cpuLT_HMS,cpuLT_uncer,cpuLT_SHMS,uncerEvts_HMS,uncerEvts_SHMS]

def calcYield() :

    [run_num,HMS_EVENTS,HMS_EVENTSun,SHMS_EVENTS,SHMS_EVENTSun,HMS_track,HMS_trackun,HMS_etrack,HMS_etrackun,SHMS_track,SHMS_trackun,SHMS_hadtrack,SHMS_hadtrackun,SHMS_pitrack,SHMS_pitrackun,SHMS_Ktrack,SHMS_Ktrackun,SHMS_ptrack,SHMS_ptrackun,ACC_EDTM,TRIG1_cut,TRIG3_cut,PS1,PS3,TIME,BCM4B,pTRIG1,pTRIG3, SENT_EDTM] = getValues()

    [current,rate_HMS,rate_SHMS,cpuLT_HMS,cpuLT_uncer,cpuLT_SHMS,uncerEvts_HMS,uncerEvts_SHMS] = findVar()

    yield_HMS = array('f',[(x*y)/(t*u*v) for x,y,t,u,v in zip(HMS_EVENTS,PS3,BCM4B,cpuLT_HMS,HMS_etrack)])
    yield_SHMS = array('f',[(x*y)/(t*u*v) for x,y,t,u,v in zip(SHMS_EVENTS,PS1,BCM4B,cpuLT_SHMS,SHMS_pitrack)])
    yieldRel_HMS = array('f',[x/yield_HMS[0] for x in yield_HMS])
    yieldRel_SHMS = array('f',[x/yield_SHMS[0] for x in yield_SHMS])

    #print("String HMS yield %s" % (yield_HMS))

    #for i in range(numRuns) :
        #print("HMS yield %0.2f" % (yield_HMS[i]))

    return[yield_HMS,yield_SHMS,yieldRel_HMS,yieldRel_SHMS]

def lumiTable(hms_rows,shms_rows):

    [run_num,HMS_EVENTS,HMS_EVENTSun,SHMS_EVENTS,SHMS_EVENTSun,HMS_track,HMS_trackun,HMS_etrack,HMS_etrackun,SHMS_track,SHMS_trackun,SHMS_hadtrack,SHMS_hadtrackun,SHMS_pitrack,SHMS_pitrackun,SHMS_Ktrack,SHMS_Ktrackun,SHMS_ptrack,SHMS_ptrackun,ACC_EDTM,TRIG1_cut,TRIG3_cut,PS1,PS3,TIME,BCM4B,pTRIG1,pTRIG3, SENT_EDTM] = getValues()

    sep = '|' 
    left = '        '
    hms_width = 167
    shms_width = 174
    tab_hms = ('-') * (hms_width-1) + sep
    tab_shms = ('-') * (shms_width-1) + sep

    fout = open('/home/trottar/ResearchNP/ROOTAnalysis/kaonlt_analysis/lumiscan/OUTPUT/LuminosityScans.txt','w') 
    fout.write('%s\n |%s, Target %s| Run Numbers ' % (tab_hms,comment,target))

    for i in range(numRuns) :
        fout.write('%s, ' % (run_num[i])) 
    fout.write('%s| \n' % (run_num[numRuns-1]))

    fout.write('-> Applied Cuts HMS: [[Ecal>0.6, Ecal<2.0, CernpeSum>2.0]]\n')
    fout.write('%s\n' % (tab_hms))

    if len(hms_rows) > 1:
        headers = hms_rows[0]._fields
        lens = []
        for i in range(len(hms_rows[0])):
            lens.append(len(str(max([ x[i] for x in hms_rows] + [headers[i]],key=lambda x:len(str(x))))))
        formats = []
        hformats = []
        for i in range(len(hms_rows[0])):
            if isinstance(hms_rows[0][i], int):
                formats.append("%%%dd" % lens[i])
            else:
                #Data
                formats.append("%%-%ds" % lens[i])
            #header
            hformats.append("%%-%ds" % lens[i])
        pattern = " | ".join(formats)
        hpattern = " | ".join(hformats)
        separator = "--".join(['-' * n for n in lens])
        fout.write(hpattern % tuple(headers) + '\n')
        fout.write('%s\n' % (tab_hms))
        _u = lambda t: t.decode('UTF-8', 'replace') if isinstance(t, str) else t
        for line in hms_rows:
            #Data
            fout.write(pattern % tuple(_u(t) for t in line) + '\n')
    elif len(hms_rows) == 1:
        hms_row = hms_rows[0]
        hwidth = len(str(max(hms_row._fields,key=lambda x: len(x))))
        for i in range(len(hms_row)):
            fout.write("%*s = %s" % (hwidth,hms_row._fields[i],hms_row[i]) + '\n')

    fout.write('%s\n' % (tab_shms))
    fout.write('-> Applied Cuts SHMS: [[Ecal>0.6, Ecal<2.0, CernpeSum>2.0]]\n')
    fout.write('%s\n' % (tab_shms))

    if len(shms_rows) > 1:
        headers = shms_rows[0]._fields
        lens = []
        for i in range(len(shms_rows[0])):
            lens.append(len(str(max([ x[i] for x in shms_rows] + [headers[i]],key=lambda x:len(str(x))))))
        formats = []
        hformats = []
        for i in range(len(shms_rows[0])):
            if isinstance(shms_rows[0][i], int):
                formats.append("%%%dd" % lens[i])
            else:
                formats.append("%%-%ds" % lens[i])
            hformats.append("%%-%ds" % lens[i])
        pattern = " | ".join(formats)
        hpattern = " | ".join(hformats)
        separator = "-.-".join(['-' * n for n in lens])
        fout.write(hpattern % tuple(headers) + '\n')
        fout.write('%s\n' % (tab_shms))
        _u = lambda t: t.decode('UTF-8', 'replace') if isinstance(t, str) else t
        for line in shms_rows:
            fout.write(pattern % tuple(_u(t) for t in line) + '\n')
    elif len(shms_rows) == 1:
        shms_row = shms_rows[0]
        hwidth = len(str(max(shms_row._fields,key=lambda x: len(x))))
        for i in range(len(shms_row)):
            fout.write("%*s = %s" % (hwidth,shms_row._fields[i],shms_row[i]) + '\n')

    fout.close()

def main() :

    [run_num,HMS_EVENTS,HMS_EVENTSun,SHMS_EVENTS,SHMS_EVENTSun,HMS_track,HMS_trackun,HMS_etrack,HMS_etrackun,SHMS_track,SHMS_trackun,SHMS_hadtrack,SHMS_hadtrackun,SHMS_pitrack,SHMS_pitrackun,SHMS_Ktrack,SHMS_Ktrackun,SHMS_ptrack,SHMS_ptrackun,ACC_EDTM,TRIG1_cut,TRIG3_cut,PS1,PS3,TIME,BCM4B,pTRIG1,pTRIG3, SENT_EDTM] = getValues()

    [current,rate_HMS,rate_SHMS,cpuLT_HMS,cpuLT_uncer,cpuLT_SHMS,uncerEvts_HMS,uncerEvts_SHMS] = findVar()

    [yield_HMS,yield_SHMS,yieldRel_HMS,yieldRel_SHMS] = calcYield()


    foutname = 'OUTPUT/plot_YieldvsCurrent_' + target + '_%i' % (run_num[0]) + '-%i' % (run_num[numRuns-1]) + '.png'

    relYieldPlot = plt.figure()

    #HMS plot
    plt.subplot(1,2,1)    
    plt.grid(zorder=1)
    plt.xlim(0,60)
    plt.ylim(0.98,1.02)
    plt.plot([0,60], [1,1], 'r-',zorder=2)
    plt.errorbar(current,yieldRel_HMS,yerr=uncerEvts_HMS,color='black',linestyle='None',zorder=3)
    plt.scatter(current,yieldRel_HMS,color='blue',zorder=4)
    plt.ylabel('Rel. Yield', fontsize=16)
    if target == 'LD2' :
        plt.title('HMS LD2 %s-%s' % (run_num[0],run_num[numRuns-1]), fontsize =16)
        plt.xlabel('Current [uA]', fontsize =16)
    elif target == 'LH2' :
        plt.title('HMS LH2 %s-%s' % (run_num[0],run_num[numRuns-1]), fontsize =16)
        plt.xlabel('Current [uA]', fontsize =16)
    else :
        plt.title('HMS Carbon %s-%s' % (run_num[0],run_num[numRuns-1]), fontsize =16)
        plt.xlabel('Current [uA]', fontsize =16)
    
    #SHMS plot
    plt.subplot(1,2,2)
    plt.grid(zorder=1)
    plt.xlim(0,60)
    plt.ylim(0.94,1.06)
    plt.plot([0,60], [1,1], 'r-',zorder=2)
    plt.errorbar(current,yieldRel_SHMS,yerr=uncerEvts_SHMS,color='black',linestyle='None',zorder=3)
    plt.scatter(current,yieldRel_SHMS,color='blue',zorder=4)
    plt.ylabel('Rel. Yield', fontsize=16)
    if target == 'LD2' :
        plt.title('SHMS LD2 %s-%s' % (run_num[0],run_num[numRuns-1]), fontsize =16)
        plt.xlabel('Current [uA]', fontsize =16)
    elif target == 'LH2' :
        plt.title('SHMS LH2 %s-%s' % (run_num[0],run_num[numRuns-1]), fontsize =16)
        plt.xlabel('Current [uA]', fontsize =16)
    else :
        plt.title('SHMS Carbon %s-%s' % (run_num[0],run_num[numRuns-1]), fontsize =16)
        plt.xlabel('Current [uA]', fontsize =16)


    plt.tight_layout()
    #plt.show()
    relYieldPlot.savefig(foutname)

    hms_tuple = namedtuple('hms_tuple',['RunNumber','Current','BeamTime','Charge','HMS_count','HMS_countuncer','Rate','PS3','Yield_HMS','RelY_HMS','Uncer_HMS','TrEff_HMS','TrEffuncer','CPULT','CPULTuncer'])

    hms_data = []
    tot_hms = []

    for i in range(numRuns) :
        hms_data.append(hms_tuple(run_num[i],round(current[i],2),round(TIME[i],2),round(BCM4B[i],2),round(HMS_EVENTS[i],2),round(HMS_EVENTSun[i],2),round(rate_HMS[i],2),round(PS3[i],2),round(yield_HMS[i],2),round(yieldRel_HMS[i],2),round(uncerEvts_HMS[i],2),round(HMS_etrack[i],2),round(HMS_etrackun[i],2),round(cpuLT_HMS[i],2),round(cpuLT_uncer[i],2)))
        tot_hms.append(hms_data[i])

    shms_tuple = namedtuple('shms_tuple',['RunNumber','Current','BeamTime','Charge','SHMS_count','SHMS_countuncer','Rate','PS3','Yield_SHMS','RelY_SHMS','Uncer_SHMS','TrEff_SHMS','TrEffuncer','CPULT','CPULTuncer'])

    shms_data = []
    tot_shms = []

    for i in range(numRuns) :
        shms_data.append(shms_tuple(run_num[i],round(current[i],2),round(TIME[i],2),round(BCM4B[i],2),round(SHMS_EVENTS[i],2),round(SHMS_EVENTSun[i],2),round(rate_SHMS[i],2),round(PS3[i],2),round(yield_SHMS[i],2),round(yieldRel_SHMS[i],2),round(uncerEvts_SHMS[i],2),round(SHMS_pitrack[i],2),round(SHMS_pitrackun[i],2),round(cpuLT_SHMS[i],2),round(cpuLT_uncer[i],2)))
        tot_shms.append(shms_data[i])

    lumiTable([tot_hms[0],tot_hms[1],tot_hms[2],tot_hms[3],tot_hms[4]],[tot_shms[0],tot_shms[1],tot_shms[2],tot_shms[3],tot_shms[4]])

if __name__=='__main__': main()
