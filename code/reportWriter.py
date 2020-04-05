## Author : GORADE PRASHANT
## Date : March 27,2019
## Jeevan Vidya 
## Revision Date : Feb 2020 CFB file compatibility added

import wx
import json
import os
import sys
import datetime
import subprocess
import time
import webbrowser
#import itertools
#from matplotlib import pyplot as plt
#import numpy as np

class MyPanel(wx.Panel):
    def __init__(self,parent):
        super(MyPanel,self).__init__(parent,style=wx.RAISED_BORDER|wx.TAB_TRAVERSAL)
        
        #font = wx.SystemSettings.GetFont(wx.SYS_SYSTEM_FONT)
        #font.Family=wx.FONTFAMILY_DEFAULT
        #font.SetPointSize(10)
        if os.name == 'posix':
            font = wx.SystemSettings.GetFont(wx.SYS_SYSTEM_FONT)
            font.Family=wx.FONTFAMILY_DEFAULT
            font.SetPointSize(9)
        else:
            font = wx.Font(wx.FontInfo(9).FaceName("Helvetica").Bold())
        self.SetFont(font)
        self.SetBackgroundColour((56, 76, 87))
        self.SetForegroundColour((255, 255, 255))
        

class myFrame(wx.Frame):
    log = open("logfile.txt","w+")
    logCount = iter(range(100))
    reportCount = 1000
    title = "title"
    def __init__(self,parent,title):
        framewidth = (445 if os.name == "posix" else 465)
        super(myFrame,self).__init__(parent,title=title,pos=(500,20),size=(framewidth,750),style= wx.MINIMIZE_BOX | wx.SYSTEM_MENU | wx.CAPTION | wx.CLOSE_BOX)
        myFrame.log.write("######## Abaqus Report Writer App Log File  ######## "+str(datetime.datetime.now().strftime('%A %b %d %Y %H:%M:%S'))+"\n\n")
        
        icon_path = imgpath + 'icon.png'
        self.SetIcon(wx.Icon(icon_path,type=wx.BITMAP_TYPE_PNG))

        self.menuBar = wx.MenuBar()
        #self.statusBar = wx.StatusBar()

        helpMenu = wx.Menu()
        helpItem = helpMenu.Append(-1,'Read Me','status msg..')
        self.menuBar.Append(helpMenu,'Help')

        #statMenu = wx.Menu()
        #statItem = statMenu.Append(-1,'Check Run Status','status msg..')
        #self.menuBar.Append(statMenu,'Status')

        aboutMenu = wx.Menu()
        aboutItem = aboutMenu.Append(-1,'About me','status msg..')
        self.menuBar.Append(aboutMenu,'About')

        self.SetMenuBar(self.menuBar)
        
        self.Bind(wx.EVT_MENU,self.help,helpItem)
        self.Bind(wx.EVT_MENU,self.onAboutDlg,aboutItem)
        #self.Bind(wx.EVT_MENU,self.stat,statItem)
        
        self.panel=MyPanel(self)
        p=self.panel
        self.gridsizer = wx.GridBagSizer(hgap=2, vgap=2)

        img = imgpath + "Panel_Image.png"
        bmp = wx.Image(img).ConvertToBitmap()
        self.logo=wx.StaticBitmap(p, -1,  bmp)
        #print("width of image = " + str(self.logo.GetSize()))


        self.Text_PYVARUSER = wx.StaticText(p,-1,"Analyst Name")
        self.Box_PYVARUSER = wx.TextCtrl(p,-1,User)

        
        self.Browse_Dlg = wx.Button(p,-1,label="Browse Utility Folder")
        self.Box_UTILPATH = wx.TextCtrl(p,-1,os.getcwd())


        self.Text_PYVARECO = wx.StaticText(p, -1, "ECO Number")
        self.Box_PYVARECO = wx.TextCtrl(p, -1, "ECO-PR-154616",size=(-1,-1))


        self.Text_PYVARBITTYPE = wx.StaticText(p, -1, "Bit - Type")
        self.Box_PYVARBITTYPE = wx.TextCtrl(p, -1, "XS616",size=(-1,-1))

        self.Text_PYVARBITSIZE = wx.StaticText(p, -1, "Bit - Size")
        self.Box_PYVARBITSIZE = wx.TextCtrl(p, -1, "122",size=(-1,-1))

        self.Text_PYVARBITBOM = wx.StaticText(p, -1, "Bit - BOM ")
        self.Box_PYVARBITBOM = wx.TextCtrl(p, -1, "8 digit",size=(-1,-1))
        self.Box_PYVARBITBOM.SetMaxLength(8)

        self.Text_PYVARGEMSNUM = wx.StaticText(p, -1, "GEMS Doc #")
        self.Box_PYVARGEMSNUM = wx.TextCtrl(p, -1, "123456789",size=(-1,-1))

        self.Text_PYVARGEMSREV = wx.StaticText(p, -1, "GEMS Rev #")
        self.Box_PYVARGEMSREV = wx.TextCtrl(p, -1, "-",size=(-1,-1))

        self.Text_PYVARBITDESNAME = wx.StaticText(p, -1, "DES or CFB File Name #")
        self.Box_PYVARBITDESNAME = wx.TextCtrl(p, -1, "67028C00",size=(-1,-1))

        self.Text_PYVARSTPFILENAME = wx.StaticText(p, -1, "PROE_StepFile_Name")
        self.Box_PYVARSTPFILENAME = wx.TextCtrl(p, -1, "60117350",size=(-1,-1))

        line1 = wx.StaticLine(p,-1,size=(30,-1),style=wx.LI_HORIZONTAL)
        line2 = wx.StaticLine(p,-1,size=(30,-1),style=wx.LI_HORIZONTAL)

        self.Text_PYVARMAT = wx.StaticText(p, -1, "Material")
        self.Combo_PYVARMAT = wx.ComboBox(p, -1, value="GM19+GB1",choices =["GM6+GB1","GM6+GB25","GM19+GB1","4130E","4140","4130M"],size=(-1,-1))
        
        self.Text_PYVARFORMATION = wx.StaticText(p, -1, "Formation")
        self.Box_PYVARFORMATION = wx.TextCtrl(p, -1, "Colton 3000",size=(-1,-1))
        
        self.Text_PYVARWOB = wx.StaticText(p, -1, "- WOB (klbf)")
        self.Box_PYVARWOB = wx.TextCtrl(p, -1, "45",size=(-1,-1))

        self.Text_PYVARRPM = wx.StaticText(p, -1, "- Total RPM")
        self.Box_PYVARRPM = wx.TextCtrl(p, -1, "180",size=(-1,-1))
        
        self.Button_1 = wx.Button(p,-1,label="RUN FEA && GENERATE REPORT")
        self.Button_2 = wx.Button(p,-1,label="RESET")
        self.Button_3 = wx.Button(p,-1,label="GENERATE REPORT ONLY")

        
        bd=2
        
        self.gridsizer.Add(self.logo,pos=(0,0),flag = wx.ALIGN_CENTER|wx.ALL,span=(1,2),border=5)
        self.gridsizer.Add(self.Text_PYVARUSER,pos=(1,0),flag = wx.ALIGN_RIGHT|wx.TOP|wx.LEFT|wx.RIGHT,span=(1,1),border=bd)
        self.gridsizer.Add(self.Box_PYVARUSER,pos=(1,1), flag=wx.EXPAND|wx.TOP|wx.LEFT|wx.RIGHT,span=(1,1),border=bd)
        self.gridsizer.Add(self.Text_PYVARECO,pos=(2,0),flag = wx.ALIGN_RIGHT|wx.TOP|wx.LEFT|wx.RIGHT,span=(1,1),border=bd)
        self.gridsizer.Add(self.Box_PYVARECO,pos=(2,1),flag=wx.EXPAND|wx.TOP|wx.LEFT|wx.RIGHT,span=(1,1),border=bd)
        self.gridsizer.Add(self.Text_PYVARBITTYPE,pos=(3,0),flag = wx.ALIGN_RIGHT|wx.TOP|wx.LEFT|wx.RIGHT,span=(1,1),border=bd)
        self.gridsizer.Add(self.Box_PYVARBITTYPE,pos=(3,1),flag=wx.EXPAND|wx.TOP|wx.LEFT|wx.RIGHT,span=(1,1),border=bd)
        self.gridsizer.Add(self.Text_PYVARBITSIZE,pos=(4,0),flag = wx.ALIGN_RIGHT|wx.TOP|wx.LEFT|wx.RIGHT,span=(1,1),border=bd)
        self.gridsizer.Add(self.Box_PYVARBITSIZE,pos=(4,1),flag=wx.EXPAND|wx.TOP|wx.LEFT|wx.RIGHT,span=(1,1),border=bd)
        self.gridsizer.Add(self.Text_PYVARBITBOM,pos=(5,0),flag = wx.ALIGN_RIGHT|wx.TOP|wx.LEFT|wx.RIGHT,span=(1,1),border=bd)
        self.gridsizer.Add(self.Box_PYVARBITBOM,pos=(5,1),flag=wx.EXPAND|wx.TOP|wx.LEFT|wx.RIGHT,span=(1,1),border=bd)
        self.gridsizer.Add(self.Text_PYVARGEMSNUM,pos=(6,0),flag = wx.ALIGN_RIGHT|wx.TOP|wx.LEFT|wx.RIGHT,span=(1,1),border=bd)
        self.gridsizer.Add(self.Box_PYVARGEMSNUM,pos=(6,1),flag=wx.EXPAND|wx.TOP|wx.LEFT|wx.RIGHT,span=(1,1),border=bd)
        self.gridsizer.Add(self.Text_PYVARGEMSREV,pos=(7,0),flag = wx.ALIGN_RIGHT|wx.TOP|wx.LEFT|wx.RIGHT,span=(1,1),border=bd)
        self.gridsizer.Add(self.Box_PYVARGEMSREV,pos=(7,1),flag=wx.EXPAND|wx.TOP|wx.LEFT|wx.RIGHT,span=(1,1),border=bd)

        self.gridsizer.Add(self.Text_PYVARBITDESNAME,pos=(8,0),flag = wx.ALIGN_RIGHT|wx.TOP|wx.LEFT|wx.RIGHT,span=(1,1),border=bd)
        self.gridsizer.Add(self.Box_PYVARBITDESNAME,pos=(8,1),flag = wx.EXPAND|wx.TOP|wx.LEFT|wx.RIGHT,span=(1,1),border=bd)

        self.gridsizer.Add(self.Text_PYVARSTPFILENAME,pos=(9,0),flag = wx.ALIGN_RIGHT|wx.TOP|wx.LEFT|wx.RIGHT,span=(1,1),border=bd)
        self.gridsizer.Add(self.Box_PYVARSTPFILENAME,pos=(9,1),flag = wx.EXPAND|wx.TOP|wx.LEFT|wx.RIGHT,span=(1,1),border=bd)
        
        self.gridsizer.Add(self.Browse_Dlg,pos=(10,0),flag = wx.EXPAND|wx.TOP|wx.LEFT|wx.RIGHT,span=(1,1),border=bd)
        self.gridsizer.Add(self.Box_UTILPATH,pos=(10,1),flag = wx.EXPAND|wx.TOP|wx.LEFT|wx.RIGHT,span=(1,1),border=bd)
        
        self.gridsizer.Add(line1,pos=(11,0),flag=wx.GROW|wx.TOP|wx.LEFT|wx.RIGHT,span=(1,2),border=bd)
        
        self.gridsizer.Add(self.Text_PYVARMAT,pos=(12,0),flag = wx.ALIGN_RIGHT|wx.TOP|wx.LEFT|wx.RIGHT,span=(1,1),border=bd)
        self.gridsizer.Add(self.Combo_PYVARMAT,pos=(12,1),flag=wx.EXPAND|wx.TOP|wx.LEFT|wx.RIGHT,span=(1,1),border=bd)
        self.gridsizer.Add(self.Text_PYVARFORMATION,pos=(13,0),flag = wx.ALIGN_RIGHT|wx.TOP|wx.LEFT|wx.RIGHT,span=(1,1),border=bd)
        self.gridsizer.Add(self.Box_PYVARFORMATION,pos=(13,1),flag=wx.EXPAND|wx.TOP|wx.LEFT|wx.RIGHT,span=(1,1),border=bd)
        self.gridsizer.Add(self.Text_PYVARWOB,pos=(14,0),flag = wx.ALIGN_RIGHT|wx.TOP|wx.LEFT|wx.RIGHT,span=(1,1),border=bd)
        self.gridsizer.Add(self.Box_PYVARWOB,pos=(14,1),flag=wx.EXPAND|wx.TOP|wx.LEFT|wx.RIGHT,span=(1,1),border=bd)
        self.gridsizer.Add(self.Text_PYVARRPM,pos=(15,0),flag = wx.ALIGN_RIGHT|wx.TOP|wx.LEFT|wx.RIGHT,span=(1,1),border=bd)
        self.gridsizer.Add(self.Box_PYVARRPM,pos=(15,1),flag=wx.EXPAND|wx.TOP|wx.LEFT|wx.RIGHT,span=(1,1),border=bd)

        self.gridsizer.Add(line2,pos=(16,0),flag=wx.GROW|wx.TOP|wx.LEFT|wx.RIGHT,span=(1,2),border=bd)
        
        self.gridsizer.Add(self.Button_1,pos=(17,0),flag = wx.ALIGN_RIGHT|wx.ALL,span=(1,1),border=bd)
        self.gridsizer.Add(self.Button_2,pos=(17,1),flag = wx.ALIGN_CENTER|wx.ALL,span=(1,1),border=bd)
        self.gridsizer.Add(self.Button_3,pos=(18,0),flag = wx.ALIGN_CENTER|wx.ALL,span=(1,2),border=bd)
                
        self.Button_1.Bind(wx.EVT_BUTTON,self.onSubmit)
        self.Button_2.Bind(wx.EVT_BUTTON,self.Reset)
        self.Button_3.Bind(wx.EVT_BUTTON,self.reportOnly)
        self.Browse_Dlg.Bind(wx.EVT_BUTTON,self.Browse)
        #self.Combo_PYVARMAT.Bind(wx.EVT_COMBOBOX,self.comboList)
        
        self.Bind(wx.EVT_CLOSE, self.onClose)
        
        p.SetSizerAndFit(self.gridsizer)
        
        myFrame.log.write(("Log " + "%2d"%next(myFrame.logCount) + ": " + "Abaqus Report Writer App Succesfully Opened "+str(datetime.datetime.now())+"\n"))
        self.onload()

        children = self.gridsizer.GetChildren()
        for child in children:
            widget = child.GetWindow()
            if isinstance(widget, wx.TextCtrl):
                widget.Bind(wx.EVT_TEXT,self.onTextEnter)
         
    def check_form(self):
        children = self.gridsizer.GetChildren()
        field_flag = 1
        for child in children:
            widget = child.GetWindow()
            if isinstance(widget, wx.TextCtrl):
                #print(widget.GetLineText(0))
                
                if widget.GetValue() == '':
                    #self.showMessage("All Fields are required. Please check for empty fields")
                    #print("I have reset color")
                    widget.SetForegroundColour(wx.Colour(255,0,0))
                    widget.AppendText("Missing Field !!")
                    field_flag = 0
        
        force_files_exist = self.check_cutterForce_files()
        #print("files found = ",force_files_exist)

        if os.path.exists(self.Box_UTILPATH.Value) and force_files_exist and field_flag==1:
            return True
        else:
            return False

    def check_cutterForce_files(self):
        cutterFiles = ["cutterfcut_bk.txt","cutterfn_bk.txt","cutterfside_bk.txt"]
        from shutil import copy
        missing_files = []
        for file in cutterFiles:
            filesrc = os.path.join(utilDir,file)
            if os.path.isfile(filesrc):
                filedst = os.getcwd() + os.sep + file
                #print("CutterFiles ",filesrc,filedst)
                copy(filesrc,filedst)
                
            else:
                missing_files.append(file)
        #print("Missing Files = ",missing_files)
        if missing_files:
            Message = "Failure: Cutter Force files named {} missing in specified location. \
                Please check utility_files folder path".format(missing_files)
            self.showMessage(Message)
            return False
        else:
            return True
                         
    def Browse(self, event):
        dialog = wx.DirDialog(self, 'Browse utility_files directory', '',
                    style=wx.DD_DEFAULT_STYLE)
        try:
            if dialog.ShowModal() == wx.ID_CANCEL:
                return
            path = dialog.GetPath()
        except Exception:
            wx.LogError('Failed to open directory!')
            raise
        finally:
            dialog.Destroy()
        if len(path) > 0:
            self.Box_UTILPATH.SetValue(path)
            #self.pg.mplayer.setCWD(path)
      
    def onTextEnter(self,event):
        #print("I am onTextEnter called")
        event.GetEventObject().SetForegroundColour(wx.Colour(0,0,0))
        
    def onClose(self,event):
        myFrame.log.write(("Log " + "%2d"%next(myFrame.logCount) + ": " + "Abaqus Report Writer App Closed "+str(datetime.datetime.now())+"\n"))
        myFrame.log.close()
        #print("Hello ",next(myFrame.logCount))
        self.Destroy()

    def createInputFile(self):
        with open('input.txt','w') as fp:
            
            bit_size = self.Box_PYVARBITSIZE.Value.strip()
            bit_type = self.Box_PYVARBITTYPE.Value.strip()
            cae_name = "_".join([bit_size,bit_type,self.bit_des])
            
            if self.cfb_file==1:
                fp.write("BIT_CFB_NAME: " + self.bit_des + "\n")
            else:
                fp.write("BIT_DES_NAME: " + self.bit_des + "\n")
            fp.write("pocket_oversize: " + "0.004" + "\n")
            fp.write("ABAQUS_CAE_NAME: " + cae_name +"\n")
            p = os.path.join(os.getcwd()+os.sep)
            p = p.replace("\\","/")
            
            fp.write("ABAQUS_CAE_Dir: " + p + "\n")
            fp.write("ABAQUS_OUTPUT_Dir: " + p +"\n")
            fp.write("ABAQUS_Scripting_Dir: " + p + "\n")
            fp.write("Initial_Job_Name: " + self.bit_des + "\n")
            fp.write("PROE_StepFile_Dir: " + p + "\n")
            fp.write("PROE_StepFile_Name: " + self.stp_file + "\n")

            mat_data = {"GM6+GB1":"33.75","GM6+GB25":"38.75","GM19+GB1":"38.75","4130E":"64","4140":"88","4130M":"96"}

            self.mat_select = self.Combo_PYVARMAT.GetValue()
            fp.write("Stress_plot_uplimit: " + mat_data[self.mat_select] +"\n")
            fp.write("Stress_plot_lowlimit: " + "-10.00" + "\n")
            myFrame.log.write(("Log " + "%2d"%next(myFrame.logCount) + ": " + "Input File successfully written "+str(datetime.datetime.now())+"\n"))

    def abaqus_run(self):
        self.bit_des = self.Box_PYVARBITDESNAME.Value.strip()
        self.stp_file = self.Box_PYVARSTPFILENAME.Value.strip()
        # check for cfb file
        if self.cfb_file == 1:
            if os.path.isfile(self.bit_des + ".cfb"):
                self.bit_des =  self.bit_des
            elif os.path.isfile(self.bit_des.upper() + ".cfb"):
                self.bit_des = self.bit_des.upper()
            elif os.path.isfile(self.bit_des.lower() + ".cfb"):
                self.bit_des = self.bit_des.lower()
            else:
                Message = "Failure: CFB File " + self.bit_des + " not found. Please check the file name."
                self.showMessage(Message)
                return None
        # print("final bit name = ",self.bit_des)
        if self.cfb_file == 0:
            if os.path.isfile(self.bit_des + ".des"):
                self.bit_des =  self.bit_des
            elif os.path.isfile(self.bit_des.upper() + ".des"):
                self.bit_des = self.bit_des.upper()
            elif os.path.isfile(self.bit_des.lower() + ".des"):
                self.bit_des = self.bit_des.lower()
            else:
                Message = "Failure: DES File " + self.bit_des + " not found. Please check the file name."
                self.showMessage(Message)
                return None
        #print("final bit name = ",self.bit_des)
        
        # check for stp file
        if os.path.isfile(self.stp_file + ".stp"):
            self.stp_file =  self.stp_file
        elif os.path.isfile(self.stp_file.upper() + ".stp"):
            self.stp_file = self.stp_file.upper()
        elif os.path.isfile(self.stp_file.lower() + ".stp"):
            self.stp_file = self.stp_file.lower() 
        else:
            self.stp_file = ''
            Message = "Failure: CAD FILE is missing " + str(self.stp_file) + ".stp"
            self.showMessage(Message)
            return None
        #print("CAD Name = ",self.stp_file)

        self.createInputFile()

        cpp_repos = ['windows_cpp.exe','linux_cpp.exe']
        cpp_file = cpp_repos[0] if os.name == 'nt' else cpp_repos[1]
        cpp_file_src = Macro_Dir + '/cpp/' + cpp_file
        cpp_file_dst = os.getcwd() + '/' + cpp_file
        
        bit_des_file = self.bit_des + ".des"
        onestepbuildfile = 'i_one_step_buildModel.py'

        from shutil import copy
        
        try:
            copy(cpp_file_src,cpp_file_dst)
            if os.name == 'nt':
                process = subprocess.check_output([cpp_file],timeout=1)

            else:
                process = subprocess.Popen([cpp_file],stdout=subprocess.PIPE)
                from threading import Timer
                timer = Timer(1,process.kill)
                timer.start()
            
        except Exception as e:
            if e.__class__.__name__=='TimeoutExpired':
                myFrame.log.write("Log " + "%2d"%next(myFrame.logCount) + ": " + "Script Generator Step Exception. " + str(e)+ "\n")
            else:
                myFrame.log.write("Log " + "%2d"%next(myFrame.logCount) + ": " + "Script Generator Step Exception. " + str(e)+ "\n")
                Message = "Failure: Script Generator Failed ! " + str(e)
                self.showMessage(Message)
                return None

        time.sleep(1)
        if os.path.isfile(onestepbuildfile):
            with open(onestepbuildfile,'a') as fp:
                fp.write("\nmdb.jobs['" + self.bit_des + "'].writeInput(consistencyChecking=OFF)\n")
                fp.write("mdb.jobs['" + self.bit_des + "'].setValues(numCpus=4, numDomains=4)\n")
                
                fp.write("flag=1\n")
                fp.write("if mdb.models['Model-1'].parts['bitbody'].elements.__len__():\n")
                fp.write("\tif not mdb.models['Model-1'].parts['bitbody'].elements[-1].type.__repr__().startswith('C3'):\n")
                fp.write("\t\tprint('******* Mesh Failed. Please do the Mesh manually *********')\n")
                fp.write("\t\tprint('******* Please Run the FEA model followed by the post processing script o4-o5.py in current working directory *******')\n")
                fp.write("\t\tflag=0\n")
                
                fp.write("p=mdb.models['Model-1'].parts['bitbody'].sets\n")
                fp.write("collection=[]\n")
                fp.write("for i in p.keys():\n")
                fp.write("\tif p[i].faces.__len__()==0 and p[i].cells.__len__()==0:\n")
                fp.write("\t\tcollection.append(i)\n")
                fp.write("if collection:\n")
                fp.write("\tflag=0\n")
                fp.write("\tprint('******* Please check failed face sets under part = {} *******'.format(collection))\n")
                fp.write("\tprint('******* Please create the face sets and run the FEA model followed by the post processing script o4-o5.py in current working directory *******')\n")

                fp.write("if flag==1:\n")
                fp.write("\tmdb.jobs['" + self.bit_des + "'].submit(consistencyChecking=OFF)\n")
                fp.write("\tprint('******* Job Running with 4 CPUS *******')\n")
                fp.write("\tprint('******* Please Wait. Abaqus solver is running *******')\n")
                
                lock_file = self.bit_des + ".lck"  
               
                fp.write("from time import sleep\n")
                fp.write("if flag==1:\n")
                fp.write("\twhile not os.path.isfile('" + lock_file + "'):\n")
                fp.write("\t\tsleep(1)\n")
                fp.write("\t\t#print('time = 1 ',os.path.isfile('" + lock_file + "'))\n")
                fp.write("\twhile os.path.isfile('" + lock_file + "'):\n")
                fp.write("\t\tsleep(1)\n")
                fp.write("\texecfile('o04_printStress.py',__main__.__dict__)\n")
                fp.write("\texecfile('o05_printBodyFaceStress.py',__main__.__dict__)\n")
                """
                if self.bitType == "steel":
                    fp.write("\texecfile('o04_printStress.py',__main__.__dict__)\n")
                    fp.write("\texecfile('o05_printBodyFaceStressMises.py',__main__.__dict__)\n")
                else:
                    fp.write("\texecfile('o04_printStress.py',__main__.__dict__)\n")
                    fp.write("\texecfile('o05_printBodyFaceStressMaxP.py',__main__.__dict__)\n")
                
                #fp.write("else:\n")
                
                #fp.write("mdb.save()\n")"""


            EM_data = {"GM6+GB1":"42100","GM6+GB25":"42100","GM19+GB1":"42100","4130E":"30000","4140":"30000","4130M":"30000"}
            with open('o4-o5.py','w') as fp:
                fp.write("execfile('o04_printStress.py',__main__.__dict__)\n")
                fp.write("execfile('o05_printBodyFaceStress.py',__main__.__dict__)\n")
                
            with open('i01_caeStartModel.py','r') as fp: mat_file_data=fp.readlines()
            with open('i01_caeStartModel.py','w') as fp:
                for line in mat_file_data:
                    if line.startswith("mdb.models['Model-1'].materials['Body']"):
                        line = "mdb.models['Model-1'].materials['Body'].Elastic(table=((" + EM_data[self.mat_select] + ", 0.3), ))" + "\n"
                        print("Material Selected ",self.mat_select,EM_data[self.mat_select])
                    fp.write(line)
            try:
                from subprocess import PIPE, Popen

                file_path = os.path.join(os.getcwd(),"i_one_step_buildModel.py")
                abaqus_path = os.path.join("C:","SIMULIA","Commands","abaqus.bat")
               
                if os.path.exists(file_path):

                    if os.name == 'nt':
                        #pass
                        proc1 = Popen([abaqus_path, 'cae', 'script={}'.format(file_path)], stdout=PIPE)
                    
                        #proc1 = Popen([abaqus_path, 'cae'], stdout=PIPE)
                    else:
                        try:
                            proc1_sub = os.system('export XLIB_SKIP_ARGB_VISUALS=1')
                            proc1 = Popen(['abq2018','cae','script={}'.format(file_path),'-mesa'], stdout=PIPE)
                        except Exception(e):
                            myFrame.log.write(("Log " + "%2d"%next(myFrame.logCount) + ": " + "Error Invoking Abaqus "+str(e)+"\n"))
                    
                    
                    rpy_reader = Macro_Dir + '/code/' + 'read_rpy.pyc'
                    while proc1.poll()!=0:
                        proc2 = Popen(['python', rpy_reader], stdin=PIPE,stdout=PIPE,stderr=PIPE)
                        print(proc2.communicate()[0].decode('utf-8'))
                        #print(proc2.communicate()[1])
                        time.sleep(5)
                        
                else: 
                    print("Bad path")
                    
                myFrame.log.write("Log " + "%2d"%next(myFrame.logCount) + ": " + "Abaqus File opened and running.. "+str(datetime.datetime.now())+"\n")
                return True
            except Exception as e:
                myFrame.log.write("Log " + "%2d"%next(myFrame.logCount) + ": " + "Problem occured while working on abaqus "+str(e)+ "\n")
        else:
            Message = "Failure: Script Generator did not run successfully. File missing " + 'i_one_step_buildModel.py'
            self.showMessage(Message)
            return None     

    def onSubmit(self,event): 
        myFrame.log.write("Log " + "%2d"%next(myFrame.logCount) + ": " + "App Form Successfully Submitted"+str(datetime.datetime.now())+"\n")
        
        self.Button_1.Disable()
        self.Button_2.Disable()
        self.Button_3.Disable()
        self.updateCFG()
        if self.check_form():
            run = self.abaqus_run()
            #print("run status ",run)
            if run:
                self.reportGenerator(abaqus_flag=1)
            else:
                self.Button_1.Enable()
                self.Button_2.Enable()
                self.Button_3.Enable()
        else:
            self.showMessage("All Fields are required. Please check for empty fields")
            self.Button_1.Enable()
            self.Button_2.Enable()
            self.Button_3.Enable()

    def reportOnly(self,event):
        self.Button_1.Disable()
        self.Button_2.Disable()
        self.Button_3.Disable()
        self.updateCFG()
        if self.check_form():
            run = self.reportGenerator(abaqus_flag=0)
        else:
            self.Button_1.Enable()
            self.Button_2.Enable()
            self.Button_3.Enable()
   
    def reportGenerator(self,abaqus_flag):
        if abaqus_flag == 0:
            self.bit_des = self.Box_PYVARBITDESNAME.Value.strip()
            self.stp_file = self.Box_PYVARSTPFILENAME.Value.strip()

        t0 = time.time()
        
        checkValue = self.checkFiles()
  
        if  checkValue == True:
            try:
                self.plotfunc()
            except Exception as e:
                myFrame.log.write("Log " + "%2d"%next(myFrame.logCount) + ": " +"Please create CutterForce.png file yourself " + str(e) + "\n")

            title = self.writeLatex()
            checkPrint = self.printReport(title)
        
            t1=time.time()

            global TITLE
        
            title = title.split(".")[0] + ".pdf"
            TITLE = title
            if checkPrint:
                t1=time.time()
                Message = "SUCCESS: Report Name " + title + " is created in Current directory in " + "%0.2f"%(t1-t0) + " sec."
                self.showMessage(Message)
                self.createUserLog(flag=1)
                
                self.Close()
            else:
                t1=time.time()
                Message = "Warning: Some information may be missing in the pdf report titled " + title + " created in \
                 currentdirectory in " + "%0.2f"%(t1-t0) + " sec."
                self.showMessage(Message)
                self.createUserLog(flag=1)                
                self.Close()

        else:
            with open("missingFiles.txt","r") as fp:
                missingFiles = [line.rstrip() for line in fp.readlines()]
                #print("Hey***********" + str(missingFiles))
            Message = "Failure: The Following Files are missing " + str(missingFiles)
            self.showMessage(Message)
            self.Button_1.Enable()
            self.Button_2.Enable()
            self.Button_3.Enable()
            self.createUserLog(flag=0)

    def plotfunc(self):
        runcommand = Macro_Dir + "/code/plotfunc.pyc"
        #print("runcommand = ", runcommand)
        process = subprocess.check_output(["python",runcommand])
        if os.path.isfile("CutterForce.png"):
            myFrame.log.write("Log " + "%2d"%next(myFrame.logCount) + ": " + "CutterForce.png created successfully from Matplotlib. "+str(datetime.datetime.now())+"\n")
        else:
            myFrame.log.write("Log " + "%2d"%next(myFrame.logCount) + ": " + "Please create CutterForce.png manually and copy in current directory. "+str(datetime.datetime.now())+"\n")

    def showMessage(self,Message):
        message = wx.MessageBox(Message,'Info',wx.OK | wx.ICON_INFORMATION)
 
    def updateCFG(self):
        p=self.panel
        if self.Box_PYVARBITTYPE.GetValue().startswith(('s','S')) or self.Box_PYVARBITTYPE.GetValue().endswith(('s','S')):
            self.bitType = "steel"
        else:
            self.bitType = "matrix"
        data={}
        data["PYVARJOBNAME"] = self.Box_PYVARBITDESNAME.Value.strip()
        data["PYVARUSER"] = self.Box_PYVARUSER.Value
        data["PYVARECO"] = self.Box_PYVARECO.Value.strip().replace("_","-").replace(" ","-")
        
        data["PYVARBITTYPE"] = self.Box_PYVARBITTYPE.Value.strip().replace("_","-").replace(" ","-")
        data["PYVARSTRESSTYPE"] = "Max. Principal"
        data["PYVARMAXPIMG"] = "MaxP" + data["PYVARJOBNAME"] + ".png"
        data["PYVARFACESTRESS"] = "MaxP_BodyFaceSet" + ".png"
        if self.bitType == "steel":
            data["PYVARSTRESSTYPE"] = "von-Mises"
            data["PYVARMAXPIMG"] = "Mises" + data["PYVARJOBNAME"] + ".png"
            data["PYVARFACESTRESS"] = "Mises_BodyFaceSet" + ".png"

        data["PYVARADDSTRESS"] = "von-Mises"
        data["PYVARADDIMG"] = "Mises" + data["PYVARJOBNAME"] + ".png"
        if self.bitType == "steel":
            data["PYVARADDSTRESS"] = "Max. Principal"
            data["PYVARADDIMG"] = "MaxP" + data["PYVARJOBNAME"] + ".png"

        data["PYVARBITSIZE"] = self.Box_PYVARBITSIZE.Value.strip().replace("_","-").replace(" ","-")
        data["PYVARBITBOM"] = self.Box_PYVARBITBOM.Value.strip().replace("_","-").replace(" ","-")[:8]
        data["PYVARBITNAME"] = data["PYVARBITSIZE"] + "-" + data["PYVARBITTYPE"] + "-" + data["PYVARBITBOM"]
        data["PYVARGEMSNUM"] = self.Box_PYVARGEMSNUM.Value.strip().replace("_","-").replace(" ","-")
        data["PYVARGEMSREV"] = self.Box_PYVARGEMSREV.Value.strip().replace("_","-").replace(" ","-")
        data["PYVARBITDESNAME"] = self.Box_PYVARBITDESNAME.Value.strip()
        data["PYVARSTPFILENAME"] = self.Box_PYVARSTPFILENAME.Value.strip()
        data["PYVARUTILFOLDER"] = self.Box_UTILPATH.Value.strip().replace("\\",'/')
        
        global utilDir
        utilDir = data["PYVARUTILFOLDER"]
       
        if self.Combo_PYVARMAT.GetValue() == "4130E":
            data["PYVARMATPROP"] = "\\small 4130E & \\small 30,000 & \\small 0.3 & \\small 80 & \\small 64 \\\\"
            data["PYVARMATLIMIT"] = "64"
            data["PYVARMATRECORD"] = "4130E"
            #data["PYVARMATNUM"] = "2"
        elif self.Combo_PYVARMAT.GetValue() == "4140":
            data["PYVARMATPROP"] = "\\small 4140 & \\small 30,000 & \\small 0.3 & \\small 110 & \\small 88 \\\\"
            data["PYVARMATLIMIT"] = "88"
            data["PYVARMATRECORD"] = "4140"
        elif self.Combo_PYVARMAT.GetValue() == "4130M":
            data["PYVARMATPROP"] = "\\small 4130M & \\small 30,000 & \\small 0.3 & \\small 120 & \\small 96 \\\\"
            data["PYVARMATLIMIT"] = "96"
            data["PYVARMATRECORD"] = "4130M"

            
        elif self.Combo_PYVARMAT.GetValue() == "GM6+GB1":
            data["PYVARMATPROP"] = "\\small GM6+GB1 & \\small 42,100 & \\small 0.3 & \\small 67.5 & \\small 33.75 \\\\"
            data["PYVARMATLIMIT"] = "33.75"
            data["PYVARMATRECORD"] = "GM6+GB1"

        elif self.Combo_PYVARMAT.GetValue() == "GM6+GB25":
            data["PYVARMATPROP"] = "\\small GM6+GB25 & \\small 42,100 & \\small 0.3 & \\small 77.5 & \\small 38.75 \\\\"
            data["PYVARMATLIMIT"] = "38.75"
            data["PYVARMATRECORD"] = "GM6+GB25"
        
        else :
            data["PYVARMATPROP"] = "\\small GM19+GB1 & \\small 42,100 & \\small 0.3 & \\small 77.5 & \\small 38.75 \\\\"
            data["PYVARMATLIMIT"] = "38.75"
            data["PYVARMATRECORD"] = "GM19+GB1"
            
        data["PYVARFORMATION"] = self.Box_PYVARFORMATION.Value.strip().replace("_","-")
        data["PYVARWOB"] = self.Box_PYVARWOB.Value.strip().replace("_","-")
        data["PYVARRPM"] = self.Box_PYVARRPM.Value.strip().replace("_","-")
        data["PYVARMESHIMG"] = "MESH_" + data["PYVARJOBNAME"] + ".png"
        data["PYVARCSTRIMG"] = "CSTR_" + data["PYVARJOBNAME"] + ".png"
        
        data["PYVARLOGO"] = imgpath + "logo1"
        data["PYVARDES"] = imgpath + "SLBBitFace"
        
        data["PYVARMAXSTRESS"] = 0
        
        if float(data["PYVARMAXSTRESS"]) >= float(data["PYVARMATLIMIT"]):
            data["PYVARCOMPARE"] = "\\color{Red}FAIL \\color{Blue}"
        else:
            data["PYVARCOMPARE"] = "\\color{Green}PASS \\color{Blue}"

        data["PYVARIMGBHA"] = os.path.join(utilDir,"bha").replace("\\","/")
        data["PYVARIMGWELL"] = os.path.join(utilDir,"well").replace("\\","/")
        data["PYVARIMGWOB"] = os.path.join(utilDir,"wob").replace("\\","/")
        data["PYVARIMGWOK"] = os.path.join(utilDir,"wob_bk").replace("\\","/")
        data["PYVARAX"] = os.path.join(utilDir,"ax_bit_1_1").replace("\\","/")
        data["PYVARAY"] = os.path.join(utilDir,"ay_bit_1_1").replace("\\","/")
        data["CFB_FILE"] = self.cfb_file

        # Write data dictionary into fea.cfg file
        try:                                                                                                                    
            with open("fea.cfg","w") as fp: json.dump(data,fp,sort_keys=True,indent=4)
            myFrame.log.write("Log " + "%2d"%next(myFrame.logCount) + ": " + "Form fields cfg file creation successfull "+str(datetime.datetime.now())+"\n")
        except:
            myFrame.log.write("Log " + "%2d"%next(myFrame.logCount) + ": " + "Form fields cfg file creation failed "+str(datetime.datetime.now())+"\n")

    def checkFiles(self):
        with open("fea.cfg","r") as fp: 
            data= json.load(fp)
            data["PYVARMESHIMG"] = 'MESH_' + self.bit_des + '.png'
            data["PYVARCSTRIMG"] = 'CSTR_' + self.bit_des + '.png'
            data["PYVARMAXPIMG"] = 'MaxP' + self.bit_des + '.png'
        with open("fea.cfg","w") as fp:
            json.dump(data,fp,sort_keys=True,indent=4)   

        reqdFiles = ["BitBodyFaceView.png","BitBodyRightView.png",data["PYVARMESHIMG"],data["PYVARCSTRIMG"],data["PYVARMAXPIMG"],data["PYVARFACESTRESS"],
                     "input.txt","maxstressMaxP.rpt","maxstressMises.rpt","cutterfcut_bk.txt","cutterfn_bk.txt",
                     "bha.png","well.png","ax_bit_1_1.png","ay_bit_1_1.png","wob.png","wob_bk.png"]
                
        missingFiles = [file for file in reqdFiles[:-8] if not os.path.isfile(file)]
        missingFiles += [file for file in reqdFiles[-8:] if not os.path.isfile(os.path.join(utilDir,file))]
        if not bool(missingFiles):    
            return True
        else:
            with open("missingFiles.txt","w") as fp:
                for file in missingFiles:
                    fp.write(file + "\n")
            return False
        
    def cropImage(self,file):
        try:
            from PIL import Image, ImageChops
            def trim(im):
                bg = Image.new(im.mode, im.size, im.getpixel((0,0)))
                diff = ImageChops.difference(im, bg)
                diff = ImageChops.add(diff, diff, 2.0, -100)
                bbox = diff.getbbox()
                if bbox:
                    return im.crop(bbox)

            im = Image.open(file)
            im = trim(im)
            im.save(file)
            myFrame.log.write("Log " + "%2d"%next(myFrame.logCount) + ": " +
                              file + "Image Cropped " + str(datetime.datetime.now())+"\n")
        except ImportError:
            myFrame.log.write("Log " + "%2d"%next(myFrame.logCount) + ": " +
                              "Pillow Package for Image Cropping is Missing " + str(datetime.datetime.now())+"\n")
            return "ImportError"
        return None

    def writeLatex(self):
        with open("fea.cfg","r") as fp:
            data= json.load(fp)

        if self.bitType == "matrix":
            report_file = "maxstressMaxP.rpt"
        else:
            report_file = "maxstressMises.rpt"

        if os.path.isfile(report_file):
            with open(report_file,"r") as gp:
                for line in gp.readlines():
                    if "Maximum" in line:
                        maxstress = float(line.split(None,1)[1])
                        data.update(PYVARMAXSTRESS="%0.2f"%maxstress)
                
        if float(data["PYVARMAXSTRESS"]) >= float(data["PYVARMATLIMIT"]):
            data["PYVARCOMPARE"] = "\\color{Red}FAIL \\color{Blue}"
        else:
            data["PYVARCOMPARE"] = "\\color{Green}PASS \\color{Blue}"
            
        imgList = [data["PYVARMESHIMG"],data["PYVARCSTRIMG"],data["PYVARMAXPIMG"],"BitBodyFaceView.png","BitBodyRightView.png"]

        imgList = iter(imgList)
        while(True):
            try:
                file = next(imgList)
                errorCheck = self.cropImage(file)
                if errorCheck == "ImportError":
                    break
            except StopIteration:
                break

        fp = open((latex_template_path+"Report_Template.tex"),"r")
        reportName = data["PYVARGEMSNUM"] + "_Rev" + data["PYVARGEMSREV"] + "_FEA_Report_" + data["PYVARJOBNAME"].split("_")[0] +".tex"
        gp = open(reportName,"w")
        count=0
        for line in fp:
            for keys in list(data.keys()):
                if keys in line:
                    line=line.replace(keys,data[keys])
                    count+=1
                    myFrame.log.write("Log " + "%2d"%next(myFrame.logCount) + ": "
                    + "Updating Latex. Line detected "+str(count) + " " + keys + " " + str(datetime.datetime.now())+"\n")
                    
                    
            gp.write(line)
        fp.close()
        gp.close()
        myFrame.log.write("Log " + "%2d"%next(myFrame.logCount) + ": " + "Latex Report Successfully Written (*.tex file) "+str(datetime.datetime.now())+"\n")
        myFrame.log.close()
        return reportName

    def printReport(self,reportName):
        #print("reportName ", reportName)
        myFrame.log = open("logfile.txt","a")
        t0=time.time()
        try:
            # latex command needs to run twice for better results 
            process = subprocess.check_output(["pdflatex", "-interaction=nonstopmode",reportName])
            process = subprocess.check_output(["pdflatex", "-interaction=nonstopmode",reportName])

            myFrame.log.write("Log " + "%2d"%next(myFrame.logCount) + ": " + "Latex Report Successfully Printed to PDF "+str(datetime.datetime.now())+"\n")    
            
            return True
        except Exception as e:
            myFrame.log.write("Log " + "%2d"%next(myFrame.logCount) + ": " + "Problem with printing -- pdfLatex "+str(e)+ "\n")
            return False

    def createUserLog(self,flag):
        file = logpath +"reportLogHistory.cfg"
            
        if os.path.isfile(file): 
            with open(file,"r") as fp: data = json.load(fp)
          
            with open(file,"w") as fp:
                if flag==1:
                    data['reportCount'] += 1
                    log = "reportCreated"
                    myFrame.log.write("Log " + "%2d"%next(myFrame.logCount) + ": " + "Internal Report Reference Number  :"+str(data['reportCount'])+"\n")
                else:
                    data['visitorCount'] += 1
                    log = "userVisited"
                    myFrame.log.write("Log " + "%2d"%next(myFrame.logCount) + ": " + "Total Number of Visitors to App :"+str(data['visitorCount'])+"\n")
                data['userLog'].append([User,log,str(datetime.datetime.now())])
                json.dump(data,fp,sort_keys=True,indent=4)
                    
    def onload(self):
        #print("I am inonload called")
        file = "fea.cfg"
        if os.path.isfile(file):
            #print("file name = ",file)
            myFrame.log.write("Log " + "%2d"%next(myFrame.logCount) + ": " + "File: fea.cfg found. Last saved form re-loaded " + str(datetime.datetime.now()) + "\n")
            with open("fea.cfg","r") as fp:
                data= json.load(fp)

            for value in data.values():
                if value == 'Missing Field !!':
                    data.values = ''
            self.Box_PYVARUSER.SetValue(data["PYVARUSER"])
            self.Box_PYVARECO.SetValue(data["PYVARECO"])
            self.Box_PYVARBITTYPE.SetValue(data["PYVARBITTYPE"])
            self.Box_PYVARBITSIZE.SetValue(data["PYVARBITSIZE"])
            self.Box_PYVARBITBOM.SetValue(data["PYVARBITBOM"])
            self.Box_PYVARGEMSNUM.SetValue(data["PYVARGEMSNUM"])
            self.Box_PYVARGEMSREV.SetValue(data["PYVARGEMSREV"])
            self.Box_UTILPATH.SetValue(data["PYVARUTILFOLDER"])
            self.Box_PYVARBITDESNAME.SetValue(data["PYVARBITDESNAME"])
            self.Box_PYVARSTPFILENAME.SetValue(data["PYVARSTPFILENAME"])
            self.Combo_PYVARMAT.SetValue(data["PYVARMATRECORD"])
            self.Box_PYVARFORMATION.SetValue(data["PYVARFORMATION"])
            self.Box_PYVARWOB.SetValue(data["PYVARWOB"])
            self.Box_PYVARRPM.SetValue(data["PYVARRPM"])
            self.cfb_file = data["CFB_FILE"]
            self.Refresh()
        else:
            myFrame.log.write("Log " + "%2d"%next(myFrame.logCount) + ": " + "Template Form loaded " + str(datetime.datetime.now()) + "\n")
            # auto read step file and des file names in current directory
            partlist = os.listdir(os.getcwd())
            filenum=0
            self.cfb_file = 0

            for part in partlist:
                if part.endswith('.stp'):
                    self.Box_PYVARSTPFILENAME.SetValue(part.split('.')[0])
                    filenum+=1

                if part.endswith('.des'):
                    self.Box_PYVARBITDESNAME.SetValue(part.split('.')[0])
                    
                    filenum+=1
                    read_bitType = None
                    try:
                        #print("part name = ", part)
                        with open(part,"r") as fp:
                            fp = iter(fp.readlines())
                            for line in fp:
                                if line.startswith("[BasicData]"):
                                    read_bitType = next(fp).rstrip()
                                    self.Box_PYVARBITTYPE.SetValue(read_bitType)
                                    break
                            if not read_bitType:
                                myFrame.log.write("Log " + "%2d"%next(myFrame.logCount) + ": " + "Bit Type not found in DES file " + str(datetime.datetime.now()) + "\n")
                    except Exception as e:
                        myFrame.log.write("Log " + "%2d"%next(myFrame.logCount) + ": " + "Could not open DES File " + str(e) + str(datetime.datetime.now()) + "\n")

                if part.endswith('.cfb'):
                    self.Box_PYVARBITDESNAME.SetValue(part.split('.')[0])
                    
                    self.cfb_file = 1
                    print("cfb file found and self.cfb_file variable is set",self.cfb_file)
                    filenum+=1

                if filenum == 2:
                    #print("I break from for loop ",len(partlist),' ',partlist.index(part))
                    break

        # Change color of text while typing
        children = self.gridsizer.GetChildren()
        for child in children:
            widget = child.GetWindow()
            if isinstance(widget, wx.TextCtrl):
                #print(widget)
                #widget.Clear() #This command Clears all text in box
                widget.SetForegroundColour(wx.Colour(128,128,128))
                   
    def Reset(self,event):
        self.Box_PYVARUSER.SetValue("Gorade Prashant")
        self.Box_PYVARECO.SetValue("ECO-PR-154616")
        self.Box_PYVARBITTYPE.SetValue("XS616")
        self.Box_PYVARBITSIZE.SetValue("122")
        self.Box_PYVARBITBOM.SetValue("67028C00")
        self.Box_PYVARGEMSNUM.SetValue("123456789")
        self.Box_PYVARGEMSREV.SetValue("-")
        self.Box_UTILPATH.SetValue(os.getcwd())
        self.Box_PYVARBITDESNAME.SetValue("67028C00")
        self.Box_PYVARSTPFILENAME.SetValue("60117350")
        self.Combo_PYVARMAT.SetValue("GM19+GB1")
        self.Box_PYVARFORMATION.SetValue("Colton 3000")
        self.Box_PYVARWOB.SetValue("45")
        self.Box_PYVARRPM.SetValue("180")
        myFrame.log.write("Log " + "%2d"%next(myFrame.logCount) + ": " +"Form was RESET"+str(datetime.datetime.now())+"\n")

        children = self.gridsizer.GetChildren()
        for child in children:
            widget = child.GetWindow()
            if isinstance(widget, wx.TextCtrl) or isinstance(widget, wx.ComboBox):
                #print(widget)
                #widget.Clear() #This command Clears all text in box
                widget.SetForegroundColour(wx.Colour(128,128,128))
                
    def help(self,event):
        url = Macro_Dir + "/help/helpfile.html"
        helplink = webbrowser.open(url)

    def onAboutDlg(self,event):
        myDialog = aboutDialog()

            
class myApp(wx.App):
    def OnInit(self):
        self.locale = wx.Locale(wx.LANGUAGE_ENGLISH)
        self.frame = myFrame(parent = None,title = "BITS FEA AUTOMATION")
        self.frame.Show()
        return True


def paths():
    global User,Macro_Dir,logpath,imgpath,latex_template_path
    User = os.environ["USER"] if os.name == "posix" else os.environ["USERNAME"]
    Macro_Dir = "/".join(sys.argv[0].split("/")[:-2]) if os.name == "posix" else "/".join(sys.argv[0].split("\\")[:-2])
    #utilDir = "/".join(os.getcwd().split("\\")) + r'/utility_files/'
    
    #print("util_Dir = ",utilDir)
    #print("Macro_Dir = ",sys.argv[0])
    logpath = (Macro_Dir + r'/log/')
    imgpath = (Macro_Dir + r'/images/') #if os.name == "posix" else (Macro_Dir + r'\images'+'\\')
    latex_template_path = (Macro_Dir + r"/latex_templates/") #if os.name =="posix" else (Macro_Dir + r"\latex_templates" + '\\')


class QaboutDialog(wx.Frame):
    def __init__(self,title):
        #self.aboutWindow = wx.Frame(None, -1,title="About",style=wx.MINIMIZE_BOX | wx.SYSTEM_MENU | wx.CAPTION | wx.CLOSE_BOX, size=(450,450))
        super(aboutDialog,self).__init__(parent=None,title=title,pos=(500,20),size=(450,450),style=wx.MINIMIZE_BOX | wx.SYSTEM_MENU | wx.CAPTION | wx.CLOSE_BOX)
        self.SetTitle("About Me")
        self.SetBackgroundColour((56, 76, 87))
        self.SetForegroundColour((255, 255, 255))
        font = wx.SystemSettings.GetFont(wx.SYS_SYSTEM_FONT)
        
        icon_path = imgpath + 'icon.png'
        self.SetIcon(wx.Icon(icon_path,type=wx.BITMAP_TYPE_PNG))
        sizer = wx.BoxSizer(wx.VERTICAL)
        Header = wx.StaticText(self, -1, "About Abaqus FEA Automation App")
        font.SetPointSize(10)

        img = imgpath + "aboutme.png"
        bmp = wx.Image(img).ConvertToBitmap()
        
        logo=wx.StaticBitmap(self, -1,  bmp)
        #print(str(logo.GetSize()))
        self.Size=(logo.GetSize()[0],400)

        line1 = wx.StaticLine(self,-1,size=(-1,-1),style=wx.LI_HORIZONTAL)

        Message = "(C) Copyright 2019. All rights reserved.\n"
        Message += "Customer Performance Center \n"
        Message += "Schlumberger India Technology Center Private Ltd."
        message = wx.StaticText(self, -1, Message)
        
        line2 = wx.StaticLine(self,-1,size=(30,-1),style=wx.LI_HORIZONTAL)

        button = wx.Button(self,-1,label="Ok")

        sizer.Add(Header, 0, wx.ALL | wx.EXPAND | wx.ALIGN_CENTER,5)
        sizer.Add(line1, 0, wx.EXPAND | wx.ALIGN_CENTER)
        sizer.Add(logo, 0, wx.EXPAND | wx.ALIGN_CENTER)
        sizer.Add(line2, 0, wx.EXPAND | wx.ALIGN_CENTER)
        sizer.Add(message, 0, wx.ALL | wx.EXPAND | wx.ALIGN_CENTER,5)
        sizer.Add(button, 0, wx.ALL | wx.ALIGN_RIGHT,5)
        button.Bind(wx.EVT_BUTTON,self.onClick)
        
        self.SetSizer(sizer)
        self.Show()

    def onClick(self,event):
        self.Close()


class aboutDialog:
    def __init__(self):
        self.aboutWindow = wx.Frame(None, -1,title="About",style=wx.MINIMIZE_BOX | wx.SYSTEM_MENU | wx.CAPTION | wx.CLOSE_BOX, size=(450,450))
        self.aboutWindow.SetTitle("About Me")
        self.aboutWindow.SetBackgroundColour((56, 76, 87))
        self.aboutWindow.SetForegroundColour((255, 255, 255))
        font = wx.SystemSettings.GetFont(wx.SYS_SYSTEM_FONT)
        
        icon_path = imgpath + 'icon.png'
        self.aboutWindow.SetIcon(wx.Icon(icon_path,type=wx.BITMAP_TYPE_PNG))
        sizer = wx.BoxSizer(wx.VERTICAL)
        Header = wx.StaticText(self.aboutWindow, -1, "About Abaqus FEA Automation App")
        font.SetPointSize(10)

        img = imgpath + "aboutme.png"
        bmp = wx.Image(img).ConvertToBitmap()
        
        logo=wx.StaticBitmap(self.aboutWindow, -1,  bmp)
        #print(str(logo.GetSize()))
        self.aboutWindow.Size=(logo.GetSize()[0],400)

        line1 = wx.StaticLine(self.aboutWindow,-1,size=(-1,-1),style=wx.LI_HORIZONTAL)

        Message = "(C) Copyright 2019. All rights reserved.\n"
        Message += "Customer Performance Center \n"
        Message += "Schlumberger India Technology Center Private Ltd."
        message = wx.StaticText(self.aboutWindow, -1, Message)
        
        line2 = wx.StaticLine(self.aboutWindow,-1,size=(30,-1),style=wx.LI_HORIZONTAL)

        button = wx.Button(self.aboutWindow,-1,label="Ok")

        sizer.Add(Header, 0, wx.ALL | wx.EXPAND | wx.ALIGN_CENTER,5)
        sizer.Add(line1, 0, wx.EXPAND | wx.ALIGN_CENTER)
        sizer.Add(logo, 0, wx.EXPAND | wx.ALIGN_CENTER)
        sizer.Add(line2, 0, wx.EXPAND | wx.ALIGN_CENTER)
        sizer.Add(message, 0, wx.ALL | wx.EXPAND | wx.ALIGN_CENTER,5)
        sizer.Add(button, 0, wx.ALL | wx.ALIGN_RIGHT,5)
        button.Bind(wx.EVT_BUTTON,self.onClick)
        
        self.aboutWindow.SetSizer(sizer)
        self.aboutWindow.Show()
    
    def onClick(self,event):
        self.aboutWindow.Close()

        
if __name__=="__main__":
    paths()
    
    app=myApp()
    print("Running........ ")
    #plotfunc()
    app.MainLoop()
    try:
        command = "evince " + str(TITLE)
        os.system(command) if os.name == "posix" else os.system(TITLE)
    except:
        print("App closed without generating report")
