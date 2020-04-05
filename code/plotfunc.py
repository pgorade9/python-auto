import itertools
import json
from matplotlib import pyplot as plt
import numpy as np

def create_dict(file):
    with open(file,"r") as gp:
        data={}
        # Get the Number of cutters mentioned in the third line of the file
        data["cutterNos"] = next(itertools.islice(gp,2,3)).split(None)[0]
        gp.seek(0)

        # Get the column names min,5%,25%,50%,75%,95%
        keys = next(itertools.islice(gp,1,2)).split(None)

        gp.seek(0)

        # Get the column names average,10%,90%
        keys+=(next(itertools.islice(gp,int(data["cutterNos"])+2,int(data["cutterNos"])+3)).split(None))

        # Add column cutterlist at zeroth position in key list
        keys.insert(0,"cutterList")

        # Define keys in dictionary named 'data'
        for key in keys: data[key] = []
        
        gp.seek(0)
        for i in itertools.islice(gp,2,int(data["cutterNos"])+2):
            len_i=len(i.split(None))
            for j in keys:
                try:
                    # Fill vaues in the column names -- cutterlist,min,5%,25%,50%,75%,95%
                    data[j].append(i.split(None)[keys.index(j)])
                except:
                    data[j]=[]
        gp.seek(0)
        for i in itertools.islice(gp,int(data["cutterNos"]) + 3, int(data["cutterNos"])+ 3 + int(data["cutterNos"]) ):
            for j in keys[-3:]:
                try:
                    # Fill vaues in the column names -- average,10%,90%
                    data[j].append(i.split(None)[keys.index(j) - len_i + 1])
                except:
                    data[j]=[]
    return data

def plotGraph():
    fileList = ["cutterfcut_bk.txt","cutterfn_bk.txt","cutterfside_bk.txt"]
    for file in fileList:
        dict_file = "ordered_data_" + file.split(".")[0] + ".cfg"
        try:
            open(file,"r")
            flag = 1
        except Exception as e:
            print("File " + file + " does not Exist " + str(e))
            flag = 0
            
        if flag != 0:
            with open(dict_file,"w") as fp:
                json.dump(create_dict(file),fp,sort_keys=True, indent=4)
                
    colors = iter(['red','blue','green'])
    UL=0
    for file in fileList:
        dict_file = "ordered_data_" + file.split(".")[0] + ".cfg"
        with open(dict_file,"r") as fp:
            data = json.load(fp)
        plot_data = data["95%"]
        plot_data.reverse()
        plot_data = [round(float(i),2) for i in plot_data]
        ul=int(float(max(plot_data)))
        x_data = data["cutterList"]
        x_data.reverse()

        # Matplot lib cannot operate on lists hence numpy arrays created here
        plot_data = np.asarray(plot_data)
        x_data = np.asarray(x_data)

        color = next(colors)
        plt.plot(x_data,plot_data,color = color, linestyle = 'solid',
                 linewidth = 1, marker = 's', markerfacecolor = color, markersize = 3,
                 label = "{} (klbf)".format(file.split(".")[0]))

        UL = ul if ul>UL else UL

        # UL + 1 selects next -- highest integer
        plt.ylim(0, UL+1) 

        plt.xticks(range(1,int(data["cutterNos"]),10))
        plt.xlabel("Cutter Number")
        plt.ylabel("Force (klbf)")
        plt.legend()
    plt.savefig("CutterForce.png")
              
if __name__=="__main__":
    plotGraph()
