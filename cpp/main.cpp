// bit_scalling.cpp : Defines the entry point for the console application.
//
//#include "stdafx.h"
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <iostream>
using namespace std;
//--------------------class for CS program-------------------------------------------------
class myString
{
public:
	char myChar[20];
};

class doubleArray //for
{
public:
	double Angle[30];
};
class Point3 //for
{
public:
	double X,Y,Z;
};
//Fuction definition
int AssignIndexIJ(myString indexIJ[18][30]);
int AssignIndexI_J(myString indexI_J[18][30]);
int AssignMatrixIJ(myString MatrixIJ[18][30],myString indexIJ[18][30],char Mat[],int BladeCnt,int bladeCutCnt[200] );

int Read_InputfileNew(char input_file[],char bitfileType[],char bit[],double &pocket_oversize,char cae_name[],char cae_dir[],
				   char odb_dir[],char py_dir[],char job_name[],char stpfile_dir[],char stpfile_name[],
				   double &uplimit,double &lowlimit);
int Set_Working_Dir(char set_working_dir[],char cae_dir[]);
int build_cae_model0(char cae_model0[],char job_name[],char cae_dir[],char cae_name[],char BitType[]);
int import_part_blade_faceNew(char importStpPy[],char stpfile_dir[],char stpfile_name[],char odb_dir[],
		int BladeCntP,double bitDia,double BLadeTipCutDia[9],double BLadeTipHeight[9],double BLadeTipRadius[9],
		int bladeAngP[10],int dBladeAngP[10],double bottom1,double bottom2,double top1,double top2,double bodyDia1,double bodyDia2);
int sect_assign(char sectAssignPy[]);
int AssignShoulderSetAuto(char autoshoulderset_file[],char shoulderSet[],
	double BitDia);
int add_instance(char instancePy[]);
int mesh_part(char meshPartPy[],double bitDia);
int bc_fixed(char bcFixedPy[]);
int Print_Stresses(char PrintStressPY[],char odb_dir[],char job_name[],
				   double uplimit,double lowlimit,char BitType[]);
int PrintBodyFaceSet_Stresses(char PrintBodyFaceSetStressPY[],char odb_dir[],char job_name[],char BitType[],int BladeCntP,double uplimit,double lowlimit);//o05
int Print_Mesh(char PrintMeshPy[], char odb_dir[], char job_name[]);
int Print_Constraint(char PrintConstraintPy[],char odb_dir[],char job_name[],myString setRPij[18][30],
		int BladeCnt,int bladeCutCnt[200]);
int Print_Load(char PrintLoadPy[],char odb_dir[],char job_name[],myString setRPij[18][30],
		int BladeCnt,int bladeCutCnt[200]);
int ReadCS_cfbfileNew(char cfa_line1[200],char cfa_line2[200],myString cutNum[200],double radius[200],
	double angArnd[200],double height[200],double prfAng[200],double bkRake[200],double sdRake[200],
	double cutDia[200],myString SizeType[200],int blade[200],int &CutNo,
	int &BladeCnt,int bladeCutCnt[18],int bladeCutNo[200],int bladeIndex[18][30],char bitcfb[20]);
int WriteCS_cfb_cfbfile(char bitcfb[20],char cfa_line1[200],char cfa_line2[200],
	double radius[200],double angArnd[200],double height[200],double prfAng[200],double bkRake[200],
	double sdRake[200],myString SizeType[200],int blade[200],int CutNo,double cutDia[200]);
//***des
int ReadCS_desfile(char bitdes[20],char BitType[],double &bitDia,int &BladeCnt,char Bit_Profile[20],
	double &ID_Radius,double &Cone_Angle,double &Shoulder_Angle,double &Nose_Radius,double &Middle_Radius,
	double &Shoulder_Radius,double &Gage_length,double &Profile_Height,double &Nose_Location_Diameter,
	double &Outside_Dia,double cutExpture[200],int insType[200],int cutTag[200],double radius[200],
	double angArnd[200],double height[200],double prfAng[200],double bkRake[200],double sdRake[200],
	double dRadius[200],double dAngArnd[200],double dHeight[200],double dPrfAng[200],double PrfAngPosi[200],
	myString SizeType[200],int blade[200],int &CutNo,int bladeCutCnt[18],int bladeCutNo[200],int bladeIndex[18][30],
	double prf_len[200],int u_pos[200],int u_bld[200],double &ConeR);
int Re_Arrange_Data(int blade[200],int CutNo,
	int &BladeCnt,int bladeCutCnt[18],int bladeCutNo[200],int bladeIndex[18][30]);
int AssignCutterDiaNew(myString SizeType[200],double cutDia[200], int CutNo);
int AssignCutterLengthNew(myString SizeType[200],double cutLen[200], int CutNo);
int WriteCS_cfbfile(char bitcfb[20],int BladeCnt,char Bit_Profile[20],
	double ID_Radius,double Cone_Angle,double Shoulder_Angle,double Nose_Radius,double Middle_Radius,
	double Shoulder_Radius,double Gage_length,double Profile_Height,double Nose_Location_Diameter,double Outside_Dia,
	double radius[200],double angArnd[200],double height[200],double prfAng[200],double prfAngPosi[200],double bkRake[200],double sdRake[200],
	myString SizeType[200],int blade[200],int CutNo,double cutDia[200]);
int IndexPrimaryCutters(int CutNo,int BladeCnt,int bladeCutCnt[18],int bladeIndex[18][30],int u_bld[200],
		int bladePtag[200],int bladePtmp[200]);
int GetPrimaryCutters(double radius[200],double angArnd[200],double height[200],double prfAng[200],double bkRake[200],
	double sdRake[200],double cutDia[200],myString SizeType[200],int bladePtmp[200],double cutLen[200],int bladePtag[200],
	int CutNo,double radiusP[200],double angArndP[200],double heightP[200],double prfAngP[200],double bkRakeP[200],
	double sdRakeP[200],double cutDiaP[200],myString SizeTypeP[200],int bladeP[200],double cutLenP[200],int &CutNoP,
	int &BladeCntP,int bladeCutCntP[18],int bladeCutNoP[200],int bladeIndexP[18][30]); //before i06
int GetPrimaryBladeDeltaAngle(double radiusP[200],double angArndP[200],double heightP[200],double cutDiaP[200],
	int bladeP[200],int BladeCntP,int bladeCutCntP[18],int bladeIndexP[18][30],int bladeAngP[9],int dBladeAngP[9],
	double BLadeTipCutDia[9],double BLadeTipHeight[9],double BLadeTipRadius[9],int BladeRotAng[10]); //before i06
int LocateBladeFacesByCylinder(char bladeface_file[15],int BladeCntP,double bitDia,
	double BLadeTipCutDia[9],double BLadeTipHeight[9],double BLadeTipRadius[9],int bladeAngP[10],int dBladeAngP[10],
	double bottom1,double bottom2,double top1,double top2,double bodyDia1,double bodyDia2);
int Read_Force95(double F95[200],char ProjName[],int CutNo,char F95_file[]);
int BldCutMatrixData(int BladeCnt,int bladeCutCnt[200],int bladeIndex[18][30],double doc[200],double Fnc95[200],
	double Ftc95[200],double Ffc95[200],double Knc[200],double Ktc[200],double Kfc[200],double DoH[18][30],
	double FTc[18][30],double FNc[18][30],double FFc[18][30],double KNc[18][30],double KFc[18][30],double KTc[18][30]);
int CtrPtsMatrixData(int BladeCnt,int bladeCutCnt[200],int bladeIndex[18][30],
		Point3 Pctr[200],Point3 PctrBij[18][30]);//assign pocket center point matrix
int AssignFaceAutoSet(char autofaceset_file[],myString Pij[18][30],int BladeCnt,int bladeCutCnt[200],
	Point3 PctrBij[18][30]);
int body_face_dimensions3(double bitDia,double bkRake[200],double height[200],double cutDia[200],
	double &bottom1,double &bottom2,double &bottom3,double &top1,double &top2,double &top3,
	double &bodyDia1,double &bodyDia2,double &bodyDia3);
int MergeSetNew(char mergedfaceset_file[],myString Pij[18][30],myString Bij[18][30],myString Sij[18][30],
	int BladeCnt,int bladeCutCnt[200],double bottom1,double bottom2,double bottom3,
	double top1,double top2,double top3,double bodyDia1,double bodyDia2,double bodyDia3);
int FcutFnFsideMatrixData(int BladeCnt,int bladeCutCnt[200],int bladeIndex[18][30],double Fcut95[200],
	double Fn95[200],double Fside95[200],double FCUT95[18][30],double FN95[18][30],double FSIDE95[18][30]);
int Write_SumFile(char sum_file[],char sumB_file[],char sumP_file[],char fcs_file[],double ROPav,double
	tq95,double tqMax,double depthAv[200],int CutNo,int sizeType[],int sizeType0);
int Write_FnFcutFside(char FnFcutFside_file[],char FnTitle[],char FcutTitle[],char FsideTitle[],
					  double Fn95[200],double Fcut95[200],double Fside95[200],int CutNo);
int Write_fcsFile(char fcs_file[],int cutNum[200],int sizeType[200],int blade[200],int bladeCutNo[200],
	double cutDia[200],double Fnc95[200],double Ftc95[200],double Ffc95[200],double Ftc95bv[200],
	double Fn95[200],double Fcut95[200],double Knc[200],double Ktc[200],double Kfc[200],int CutNo);
int Bit_DoH(char dohScript[],double doc[200],
	myString Cij[18][30],double DoH[18][30],int BladeCnt,int bladeCutCnt[200],int CutNo);
int Cutter_FcutFnFside_load(char FcutFnFsidePY[],myString FCUTij[18][30],myString FNij[18][30],myString FSIDEij[18][30],
		double FCUT95[18][30],double FN95[18][30],double FSIDE95[18][30],int BladeCnt,int bladeCutCnt[200],int CutNo,
		char ProjName[]);
int writePTS_file(char pts_file[15],int CutNo,double radius[200],double angArnd[200],
	double height[200],double prfAng[200],double bkRake[200],double sdRake[200],
	Point3 Point0,Point3 Point[200]);
int writePTS_file_ptNew(char pts_file[15],int CutNo,double radius[200],double angArnd[200],double cutLen[200],
	double height[200],double prfAng[200],double bkRake[200],double sdRake[200],double cutDia[200],
	Point3 Point[200],double pocket_oversize); //find center point coordinates of pocket face
int writePTS_file_side_ptNew(char pts_file[15],int CutNo,double radius[200],double angArnd[200],double cutLen[200],
	double height[200],double prfAng[200],double bkRake[200],double sdRake[200],double cutDia[200],
	Point3 Point[200],double pocket_oversize); //find side point coordinates of pocket face
int writePTS_file_PcylBtm_pt(char pts_file[15],int CutNo,double radius[200],double angArnd[200],double cutLen[200],
	double height[200],double prfAng[200],double bkRake[200],double sdRake[200],double cutDia[200],
	Point3 Point[200],double pocket_oversize); //find center point coordinates of bottom cylinder face
int writePTS_file_PcylTop_pt(char pts_file[15],int CutNo,double radius[200],double angArnd[200],double cutLen[200],
	double height[200],double prfAng[200],double bkRake[200],double sdRake[200],double cutDia[200],
	Point3 Point[200],double pocket_oversize); //find center point coordinates of bottom cylinder face
int AssignPocketSetFaceByBoundingCylinder(char pocket_faceset_file[30],myString Pij[18][30],int BladeCnt,int bladeCutCnt[200],
	Point3 PcylBtmBij[18][30],Point3 PcylTopBij[18][30],double cutDia[200],int bladeIndex[18][30],double bottom1,double bottom2,double bottom3,
	double top1,double top2,double top3,double bodyDia1,double bodyDia2,double bodyDia3);
int writeCordPts_file(char CordPts_file[15],int CutNo,Point3 Pointo[200],Point3 Pointx[200],Point3 Pointy[200]);
int BldPtsMatrixData(char ptsBij_file[15],int BladeCnt,int bladeCutCnt[200],int bladeIndex[18][30],
		Point3 Po[200],Point3 Px[200],Point3 Py[200],
		Point3 PoBij[18][30],Point3 PxBij[18][30],Point3 PyBij[18][30]);
int WriteAssignCordsPS(char cordcspy_file[],myString CSij[18][30],myString Pij[18][30],int BladeCnt,
				int bladeCutCnt[200],Point3 PoBij[18][30],Point3 PxBij[18][30],Point3 PyBij[18][30]);
int WriteAssignRPsPS(char rpspy_file[],myString RPSij[18][30],myString RPij[18][30],myString setRPij[18][30],
					 int BladeCnt,int bladeCutCnt[200],Point3 PoBij[18][30]);
int Pocket_Beam_Constr(char addConstraint[],myString Pij[18][30],myString setRPij[18][30],
		myString Beamij[18][30],myString CSij[18][30],int BladeCnt,int bladeCutCnt[200]);
int Cutter_Fcut0_LoadZ(char Fcut10Script[],myString setRPij[18][30],myString Pij[18][30],myString CSij[18][30],
		myString FCUTij[18][30],int BladeCnt,int bladeCutCnt[200]);
int Cutter_Fn0_LoadX(char Fn10Script[],myString setRPij[18][30],myString Pij[18][30],myString CSij[18][30],
		myString FNij[18][30],int BladeCnt,int bladeCutCnt[200]);
int Cutter_Fside0_LoadY(char Fside10Script[],myString setRPij[18][30],myString Pij[18][30],myString CSij[18][30],
		myString FSIDEij[18][30],int BladeCnt,int bladeCutCnt[200]);
int build_model_scripts(char build_model[],char py_dir[],char set_working_dir[],char cae_model0[],//force file extension
	char importStpPy[],char sectAssignPy[],char meshPartPy[],char autobotfaceset_file[],char autosidefaceset_file[],
	char mergedfaceset_file[],char cordcspy_file[],char instancePy[],char rpspy_file[],char addConstraint[],
	char Fcut10Script[],char Fn10Script[],char Fside10Script[],char autoshoulderset_file[],
	char bcFixedPy[],char FcutFnFsidePY[],char PrintMeshPy[],char PrintConstraintPy[],char PrintLoadPy[]);
int build_model_scriptsNew(char build_model[],char py_dir[],char set_working_dir[],char cae_model0[],//force file extension
	char importStpPy[],char sectAssignPy[],char meshPartPy[],char pocket_faceset_file[],char autobotfaceset_file[],char autosidefaceset_file[],
	char mergedfaceset_file[],char cordcspy_file[],char instancePy[],char rpspy_file[],char addConstraint[],
	char Fcut10Script[],char Fn10Script[],char Fside10Script[],char autoshoulderset_file[],
	char bcFixedPy[],char FcutFnFsidePY[],char PrintMeshPy[],char PrintConstraintPy[],char PrintLoadPy[]);
int FindingPocketFaceSet(char find_pocket_set_file[],char py_dir[],char autobotfaceset_file[],char autosidefaceset_file[],char mergedfaceset_file[]);

int main()
{
	cout<<"****PDC Blade ABAQUS FEA Scripting Program by Zhehua Joshua Zhang *******"<<endl;
	cout<<"This program is used to create I/O scripts for FEA blade stress in ABAQUS"<<endl;
	cout<<"PLease put this scripting program with input.txt in a directory, which also"<<endl;
	cout<<"include bit des file, IDEAS cutterfn_bk.txt, cutterfcut_bk.txt and "<<endl;
	cout<<"cutterfside_bk.txt files as the inputfor Scripting"<<endl;
	cout<<"The program will generate several python script files for ABAQUS I/O scripting"<<endl;
	cout<<endl;
	double pi=3.141592654;

	int CutNo=0,CutNoP=0;//for input bit
	char BitType[]="SteelBit";
	double bitDia;
	double ID_Radius=0.0,Cone_Angle,Shoulder_Angle=0.0,Nose_Radius=0.0,Middle_Radius=0.0;
	double Shoulder_Radius=0.0,Gage_length=0.0,Profile_Height=0.0,Nose_Location_Diameter=0.0;
	double Outside_Dia=0.0,ConeR=0.0;
	double cutExpture[200];
	char Bit_Profile[20];
	int insType[200],cutTag[200];
	myString SizeType[200],SizeTypeP[200];
	double prf_len[200];
	int u_pos[200],u_bld[200];
	double radius[200],angArnd[200],height[200],prfAng[200],bkRake[200],bkRake0[200];
	double sdRake[200],sdRake0[200],cutDia[200],pocketDia[200],cutLen[200];//for input bit
	double dRadius[200],dAngArnd[200],dHeight[200],dPrfAng[200],prfAngPosi[200];
	int sizeType[200],blade[200];//for input bit
	int BladeCnt=0,BladeCntP=0;
	int bladeCutCnt[18],bladeCutCntP[18];//cutter count for each blade
	int bladeCutNo[200],bladeCutNoP[200];//for input bit
	int bladeIndex[18][30],bladeIndexP[18][30];//number of blades and number of cutters on the blade
	int bladePtag[200],bladePtmp[200],bladeP[200];//used to indentify primary blade
	double radiusP[200],angArndP[200],heightP[200],prfAngP[200],bkRakeP[200],sdRakeP[200];
	double cutDiaP[200],cutLenP[200];//for input bit
	double Fn95[200],Fcut95[200],Fside95[200];
	double FCUT95[18][30],FN95[18][30],FSIDE95[18][30];
	Point3 Po0,Px0,Py0;//original points
	Point3 Po[200],Px[200],Py[200],Pctr[200],Pside[200];//converted origin, X and Y points
	Point3 PoBij[18][30],PxBij[18][30],PyBij[18][30],PctrBij[18][30],PsideBij[18][30];//converted origin, X and Y points
    double shankID=3.0,bodybotZ=-5.0;
	int I;
	for (I=0;I<18;I++)
	{
		bladeCutCnt[I]=0;
		bladeCutCntP[I]=0;
	}//assign all to zero
	char input_file[]="input.txt";
	double pocket_oversize;
	//char cae_name[40],cae_dir[60],odb_dir[60],py_dir[60],job_name[30],stpfile_dir[50],stpfile_name[30];//force file extension
	char cae_name[40],cae_dir[100],odb_dir[100],py_dir[100],job_name[30],stpfile_dir[100],stpfile_name[30];//force file extension
	char set_working_dir[]="i00_setWorkingDir.py";//force file extension
	char cae_model0[]="i01_caeStartModel.py";//force file extension
	char importStpPy[]="i02_importPart.py";//force file extension
	char sectAssignPy[]="i03_sectionAssignment.py";//force file extension
	char meshPartPy[]="i04_meshPart.py";//force file extension
	char pocket_faceset_file[]="i05_findPocketFaceSet_pij.py";//by Cylinder
	char autobotfaceset_file[]="i05_pocketBottomFaceSet_bij.py";
	char autosidefaceset_file[]="i06_pocketSideFaceSet_sij.py";
	char mergedfaceset_file[]="i07_mergedPocketFaceSet_pij.py";
	char cordcspy_file[]="i08_cutterTipCordCsij.py";//assign pij to csij
	char instancePy[]="i09_addInstance.py";//force file extension
	char rpspy_file[]="i10_cutterTipRefPoint.py";//assign pij to csij
	char addConstraint[]="i11_addConstraint.py";
	char Fcut10Script[]="i12_addFcut10.py";
	char Fn10Script[]="i13_addFn10.py";
	char Fside10Script[]="i14_addFside10.py";
	char autoshoulderset_file[]="i15_shoulderSet.py";//force file extension
	char bcFixedPy[]="i16_bcFixed.py";//force file extension
	char build_model[]="i_one_step_buildModel.py";//force file extension
	char build_modelOld[]="i_one_step_buildModelOld.py";//force file extension
	char find_pocket_set_file[]="i_pocket_face_sets_by_findat_points.py";//build model
	char PrintMeshPy[]="o01_printMesh.py";//force file extension
	char PrintConstraintPy[]="o02_printConstraint.py";//****** o02 *****
	char PrintLoadPy[]="o03_printLoad.py";//force file extension
	char PrintMaxPPy[]="o03_printMaxP.py";//force file extension
	char PrintStressPY[]="o04_printStress";//force file extension
	char PrintBodyFaceSetStressPY[]="o05_printBodyFaceStress";//*****05******
	char MaxPPy[]="MaxP.py";//force file extension	char cordpy_file[]="cordpij.py";
	char MisesPy[]="Mises.py";//force file extension	char cordpy_file[]="cordpij.py";

	char bit[]="00000a00";
	char bitdes[20],bitcfb[20];//primary cutter and backup cutter bit
	char des[]=".des";
	char cfb[]=".cfb";
	char cfa_line1[200];
	char cfa_line2[200];
	char FcutFnFside[]="_FcutFnFside.py";
	char FcutFnFsidePY[80];
	char FnFcutFside_file[]="FnFcutFside_sum.txt";

	char FnTitle[]="Fn";
	char FcutTitle[]="Fcut";
	char FsideTitle[]="Fside";
	char Fn_file[]="cutterfn_bk.txt";
	char Fcut_file[]="cutterfcut_bk.txt";
	char Fside_file[]="cutterfside_bk.txt";
	char dummy[20],ProjName[200];
	char shoulderSet[]="shoulder";
//assign matrix string*****************************************************************************************
	myString indexIJ[18][30];
	AssignIndexIJ(indexIJ);
	myString indexI_J[18][30];
	AssignIndexI_J(indexI_J);
//end assign Matrix string*************************************************************************************

	double uplimit, lowlimit;
	char bitfileType[30];
	Read_InputfileNew(input_file,bitfileType,bit,pocket_oversize,cae_name,cae_dir,
		odb_dir,py_dir,job_name,stpfile_dir,stpfile_name,uplimit,lowlimit);
//*add
	strcpy(bitdes,bit);
	strcpy (bitdes+strlen(bitdes),des);
	char bitcfbnew[30];
	char cfbnew[]="new.cfb";

	strcpy(bitcfb,bit);
	strcpy (bitcfb+strlen(bitcfb),cfb);
	strcpy(bitcfbnew,bit);
	strcpy (bitcfbnew+strlen(bitcfbnew),cfbnew);

	strcpy(FcutFnFsidePY,"i17_");
	strcpy (FcutFnFsidePY+strlen(FcutFnFsidePY),bit);
	strcpy (FcutFnFsidePY+strlen(FcutFnFsidePY),FcutFnFside);
	//add*
	strcpy (bit+strlen(bit),cfb);
	myString cutNum[200];

	if (bitfileType[4]=='C'||bitfileType[4]=='c')
	{
		ReadCS_cfbfileNew(cfa_line1,cfa_line2,cutNum,radius,angArnd,height,prfAng,bkRake,sdRake,
			cutDia,SizeType,blade,CutNo,BladeCnt,bladeCutCnt,bladeCutNo,bladeIndex,bitcfb);
		bitDia=2.0*radius[CutNo-1];
		for (I=0;I<CutNo;I++)
		{
			sdRake[I]=-sdRake[I];//side rake is negative in cfb file
			u_bld[I]=blade[I];
			prfAngPosi[I]=prfAng[I];
		}//assign correct value
		WriteCS_cfb_cfbfile(bitcfbnew, cfa_line1,cfa_line2,radius,angArnd,height,prfAng,bkRake,
			sdRake,SizeType,blade,CutNo,cutDia);
	}
	else
	{
		ReadCS_desfile(bitdes,BitType,bitDia,BladeCnt,Bit_Profile,ID_Radius,Cone_Angle,
			Shoulder_Angle,Nose_Radius,Middle_Radius,Shoulder_Radius,Gage_length,Profile_Height,
			Nose_Location_Diameter,Outside_Dia,cutExpture,insType,cutTag,radius,angArnd,height,
			prfAng,bkRake,sdRake,dRadius,dAngArnd,dHeight,dPrfAng,prfAngPosi,
			SizeType,blade,CutNo,bladeCutCnt,bladeCutNo,bladeIndex,prf_len,u_pos,u_bld,ConeR);
			Re_Arrange_Data(blade,CutNo,BladeCnt,bladeCutCnt,bladeCutNo,bladeIndex);
			prfAngPosi[0]=prfAng[0];
			AssignCutterDiaNew(SizeType,cutDia,CutNo);
		WriteCS_cfbfile(bitcfb,BladeCnt,Bit_Profile,ID_Radius,Cone_Angle,Shoulder_Angle,Nose_Radius,Middle_Radius,
		Shoulder_Radius,Gage_length,Profile_Height,Nose_Location_Diameter,Outside_Dia,radius,angArnd,height,
		prfAng,prfAngPosi,bkRake,sdRake,SizeType,blade,CutNo,cutDia);
	}

	AssignCutterLengthNew(SizeType,cutLen,CutNo);
//new********************
	IndexPrimaryCutters(CutNo,BladeCnt,bladeCutCnt,bladeIndex,u_bld,bladePtag,bladePtmp); //index to seperate primary blade
	GetPrimaryCutters(radius,angArnd,height,prfAng,bkRake,sdRake,cutDia,SizeType,bladePtmp,cutLen,bladePtag,
	CutNo,radiusP,angArndP,heightP,prfAngP,bkRakeP,sdRakeP,cutDiaP,SizeTypeP,bladeP,cutLenP,CutNoP,
	BladeCntP,bladeCutCntP,bladeCutNoP,bladeIndexP);
	int bladeAngP[9],dBladeAngP[9],BladeRotAng[10];
	double BLadeTipCutDia[9],BLadeTipHeight[9],BLadeTipRadius[9];
	double MultiI=0.2,MultiO=0.4;
	GetPrimaryBladeDeltaAngle(radiusP,angArndP,heightP,cutDiaP,bladeP,BladeCntP,bladeCutCntP,bladeIndexP,
	bladeAngP,dBladeAngP,BLadeTipCutDia,BLadeTipHeight,BLadeTipRadius,BladeRotAng);
	double bottom1,bottom2,bottom3,top1,top2,top3,bodyDia1,bodyDia2,bodyDia3;
	body_face_dimensions3(bitDia,bkRake,height,cutDia,bottom1,bottom2,bottom3,top1,top2,top3,bodyDia1,bodyDia2,bodyDia3);// before i04

//assign Mij

	char FCUTij0[]="fcut";
	myString FCUTij[18][30];
	AssignMatrixIJ(FCUTij, indexIJ,FCUTij0,BladeCnt,bladeCutCnt);
	char FNij0[]="fn";
	myString FNij[18][30];
	AssignMatrixIJ(FNij, indexIJ,FNij0,BladeCnt,bladeCutCnt);
	char FSIDEij0[]="fside";
	myString FSIDEij[18][30];
	AssignMatrixIJ(FSIDEij, indexIJ,FSIDEij0,BladeCnt,bladeCutCnt);

	char Pij0[]="p";
	myString Pij[18][30];
	AssignMatrixIJ(Pij, indexIJ,Pij0,BladeCnt,bladeCutCnt);

	char Bij0[]="b";
	myString Bij[18][30];
	AssignMatrixIJ(Bij, indexIJ,Bij0,BladeCnt,bladeCutCnt);

	char Sij0[]="s";
	myString Sij[18][30];
	AssignMatrixIJ(Sij, indexIJ,Sij0,BladeCnt,bladeCutCnt);

	char Cij0[]="c";
	myString Cij[18][30];
	AssignMatrixIJ(Cij, indexIJ,Cij0,BladeCnt,bladeCutCnt);

//for cord variable
	char CSij0[]="cs";
	myString CSij[18][30];
	AssignMatrixIJ(CSij, indexI_J,CSij0,BladeCnt,bladeCutCnt);

	char RPSij0[]="rp";
	myString RPSij[18][30];
	AssignMatrixIJ(RPSij, indexI_J,RPSij0,BladeCnt,bladeCutCnt);

	char RPij0[]="RP";
	myString RPij[18][30];
	AssignMatrixIJ(RPij, indexIJ,RPij0,BladeCnt,bladeCutCnt);

	char setRPij0[]="rp";
	myString setRPij[18][30];
	AssignMatrixIJ(setRPij, indexIJ,setRPij0,BladeCnt,bladeCutCnt);

	char Beamij0[]="beam";
	myString Beamij[18][30];
	AssignMatrixIJ(Beamij, indexIJ,Beamij0,BladeCnt,bladeCutCnt);

//********************
	Set_Working_Dir(set_working_dir,cae_dir); //i00
	build_cae_model0(cae_model0,job_name,cae_dir,cae_name,BitType); //i01
	import_part_blade_faceNew(importStpPy,stpfile_dir,stpfile_name, odb_dir,BladeCntP,bitDia,BLadeTipCutDia,BLadeTipHeight,BLadeTipRadius,
	bladeAngP,dBladeAngP,bottom1,bottom2,top1,top2,bodyDia1,bodyDia2);//i02
	sect_assign(sectAssignPy);//i03
	mesh_part(meshPartPy,bitDia);//i04

//***********insert modelling script****************************************
	char Opts_file[]="o_points.pts";
	char Xpts_file[]="x_points.pts";
	char Ypts_file[]="y_points.pts";
	char CordPts_file[]="Cord_oxy_points.txt";
	char ptsBij_file[]="oxyBij_points.txt";

	Po0.X=0.0;Po0.Y=0.0;Po0.Z=0.0;
	Px0.X=0.0;Px0.Y=0.1;Px0.Z=0.0;
	Py0.X=0.1;Py0.Y=0.0;Py0.Z=0.0;
	for (I=0;I<200;I++)
	{
		bkRake0[I]=0.0;
		sdRake0[I]=0.0;
	}//assign all to zero

	for (I=0;I<200;I++)
	{
		sdRake[I]=-sdRake[I];
	}//assign all negtive due to sign writePTS_file

	writePTS_file(Opts_file,CutNo,radius,angArnd,height,prfAngPosi,bkRake0,sdRake0,Po0,Po);
	writePTS_file(Xpts_file,CutNo,radius,angArnd,height,prfAngPosi,bkRake0,sdRake0,Px0,Px);
	writePTS_file(Ypts_file,CutNo,radius,angArnd,height,prfAngPosi,bkRake0,sdRake0,Py0,Py);
//	writeCordPts_file(CordPts_file,CutNo,Po,Px,Py);
	BldPtsMatrixData(ptsBij_file,BladeCnt,bladeCutCnt,bladeIndex,Po,Px,Py,PoBij,PxBij,PyBij);
//**********find central points of pocket
	char pocket_cntpts_file[]="pt_cnt_points.pts";
	writePTS_file_ptNew(pocket_cntpts_file,CutNo,radius,angArnd,cutLen,height,prfAng,bkRake,sdRake,cutDia,Pctr,pocket_oversize);
	CtrPtsMatrixData(BladeCnt,bladeCutCnt,bladeIndex,Pctr,PctrBij);//assign pocket center point matrix
	AssignFaceAutoSet(autobotfaceset_file,Bij,BladeCnt,bladeCutCnt,PctrBij);//i05
//**********find side points of pocket
	char pocket_sidepts_file[]="pt_side_points.pts";
	writePTS_file_side_ptNew(pocket_sidepts_file,CutNo,radius,angArnd,cutLen,height,prfAng,bkRake,sdRake,cutDia,Pside,pocket_oversize);
	CtrPtsMatrixData(BladeCnt,bladeCutCnt,bladeIndex,Pside,PsideBij);//assign pocket center point matrix
	AssignFaceAutoSet(autosidefaceset_file,Sij,BladeCnt,bladeCutCnt,PsideBij);//i06

	MergeSetNew(mergedfaceset_file,Pij,Bij,Sij,BladeCnt,bladeCutCnt,bottom1,bottom2,bottom3,top1,top2,top3,bodyDia1,bodyDia2,bodyDia3);//i07
	cout<<endl;

//**********find bottom points of pocket cyl
	Point3 PcylBtm[200],PcylBtmBij[18][30];//cylindral botoom and top point for pocket
	char pocket_cylBtm_pts_file[]="pt_cylBtm_points.pts";
	writePTS_file_PcylBtm_pt(pocket_cylBtm_pts_file,CutNo,radius,angArnd,cutLen,height,prfAng,bkRake,sdRake,cutDia,PcylBtm,pocket_oversize);
	CtrPtsMatrixData(BladeCnt,bladeCutCnt,bladeIndex,PcylBtm,PcylBtmBij);//assign pocket center point matrix
//**********find top points of pocket cyl
	Point3 PcylTop[200],PcylTopBij[18][30];//cylindral botoom and top point for pocket
	char pocket_cylTop_pts_file[]="pt_cylTop_points.pts";
	writePTS_file_PcylTop_pt(pocket_cylTop_pts_file,CutNo,radius,angArnd,cutLen,height,prfAng,bkRake,sdRake,cutDia,PcylTop,pocket_oversize);
	CtrPtsMatrixData(BladeCnt,bladeCutCnt,bladeIndex,PcylTop,PcylTopBij);//assign pocket center point matrix

    AssignPocketSetFaceByBoundingCylinder(pocket_faceset_file,Pij,BladeCnt,bladeCutCnt,PcylBtmBij,PcylTopBij,cutDia,bladeIndex,
		bottom1,bottom2,bottom3,top1,top2,top3,bodyDia1,bodyDia2,bodyDia3);//i07new

	WriteAssignCordsPS(cordcspy_file,CSij,Pij,BladeCnt,bladeCutCnt,PoBij,PxBij,PyBij); //i08
	add_instance(instancePy);//i09
	WriteAssignRPsPS(rpspy_file,RPSij,RPij,setRPij,BladeCnt,bladeCutCnt,PoBij); //i10
	Pocket_Beam_Constr(addConstraint,Pij,setRPij,Beamij,CSij,BladeCnt,bladeCutCnt);//i11
    Cutter_Fcut0_LoadZ(Fcut10Script,setRPij,Pij,CSij,FCUTij,BladeCnt,bladeCutCnt); //i12
    Cutter_Fn0_LoadX(Fn10Script,setRPij,Pij,CSij,FNij,BladeCnt,bladeCutCnt); //i13
    Cutter_Fside0_LoadY(Fside10Script,setRPij,Pij,CSij,FSIDEij,BladeCnt,bladeCutCnt);//i14
	AssignShoulderSetAuto(autoshoulderset_file,shoulderSet,bitDia); //i15
	bc_fixed(bcFixedPy);//i16
	cout<<endl;
	Read_Force95(Fside95,ProjName,CutNo,Fside_file); //6
	Read_Force95(Fcut95,ProjName,CutNo,Fcut_file); //4
	Read_Force95(Fn95,ProjName,CutNo,Fn_file); //5
	cout<<"Project: "<<ProjName<<endl;

	FcutFnFsideMatrixData(BladeCnt,bladeCutCnt,bladeIndex,Fcut95,Fn95,Fside95,FCUT95,FN95,FSIDE95);

    Write_FnFcutFside(FnFcutFside_file,FnTitle,FcutTitle,FsideTitle,Fn95,Fcut95,Fside95,CutNo);

	Cutter_FcutFnFside_load(FcutFnFsidePY,FCUTij,FNij,FSIDEij,FCUT95,FN95,FSIDE95,BladeCnt,bladeCutCnt,CutNo,ProjName);//i17
	cout<<endl;
	build_model_scriptsNew(build_model,py_dir,set_working_dir,cae_model0,importStpPy,sectAssignPy,meshPartPy,
					pocket_faceset_file,autobotfaceset_file,autosidefaceset_file,mergedfaceset_file,
					cordcspy_file,instancePy,rpspy_file,addConstraint,Fcut10Script,
					Fn10Script,Fside10Script,autoshoulderset_file,bcFixedPy,FcutFnFsidePY,
					PrintMeshPy,PrintConstraintPy,PrintLoadPy);
	build_model_scripts(build_modelOld,py_dir,set_working_dir,cae_model0,importStpPy,sectAssignPy,meshPartPy,
					autobotfaceset_file,autosidefaceset_file,mergedfaceset_file,
					cordcspy_file,instancePy,rpspy_file,addConstraint,Fcut10Script,
					Fn10Script,Fside10Script,autoshoulderset_file,bcFixedPy,FcutFnFsidePY,
					PrintMeshPy,PrintConstraintPy,PrintLoadPy);
	FindingPocketFaceSet(find_pocket_set_file,py_dir,autobotfaceset_file,autosidefaceset_file,mergedfaceset_file);

	Print_Mesh(PrintMeshPy,odb_dir,job_name); //o01
	Print_Constraint(PrintConstraintPy,odb_dir,job_name,setRPij,BladeCnt,bladeCutCnt); //o02
	Print_Load(PrintLoadPy,odb_dir,job_name,setRPij,BladeCnt,bladeCutCnt); //o03
	Print_Stresses(PrintStressPY,odb_dir,job_name,uplimit,lowlimit,BitType);//o04
	PrintBodyFaceSet_Stresses(PrintBodyFaceSetStressPY,odb_dir,job_name,BitType,BladeCntP,uplimit,lowlimit);//o05

	//*******************
	cout<<endl;
	cout<<"Calculation is done!"<<endl;
	cin.ignore();
	cin.ignore();
	return 0;
}

int Read_InputfileNew(char input_file[],char bitfileType[],char bit[],double &pocket_oversize,char cae_name[],char cae_dir[],
				   char odb_dir[],char py_dir[],char job_name[],char stpfile_dir[],char stpfile_name[],
				   double &uplimit,double &lowlimit)
	{
		ifstream input;
		input.open (input_file);		// input connects to file input_file
		if (input.fail ())
		{
		cerr << "*** ERROR: Cannot open " << input_file
		<< " for input." << endl;
		cin.ignore();
		cin.ignore();
		return EXIT_FAILURE;	// failure return
		} // end if
		cout<<input_file<<"  opened for input initial data"<<endl;

		input>>bitfileType;input>>bit;input.ignore(80,'\n');
		input.ignore(80,':');input>>pocket_oversize;input.ignore(80,'\n');
		input.ignore(80,':');input>>cae_name;input.ignore(80,'\n');
		input.ignore(80,':');input>>cae_dir;input.ignore(80,'\n');
		input.ignore(80,':');input>>odb_dir;input.ignore(80,'\n');
		input.ignore(80,':');input>>py_dir;input.ignore(80,'\n');
		input.ignore(80,':');input>>job_name;input.ignore(80,'\n');
		input.ignore(80,':');input>>stpfile_dir;input.ignore(80,'\n');
		input.ignore(80,':');input>>stpfile_name;input.ignore(80,'\n');
		input.ignore(80,':');input>>uplimit;input.ignore(80,'\n');
		input.ignore(80,':');input>>lowlimit;input.ignore(80,'\n');
		input.close ();			// close input file stream
		return 0;
	} //end input file new

int Re_Arrange_Data(int blade[200],int CutNo,
	int &BladeCnt,int bladeCutCnt[18],int bladeCutNo[200],int bladeIndex[18][30])
	{
		int I;

		for (I=0;I<BladeCnt;I++)
		{
				bladeCutCnt[I]=0;
		}//assign all to zero
		BladeCnt=0;
		for (I=0;I<CutNo;I++)
		{
				if(blade[I]>BladeCnt)
					BladeCnt=blade[I];
				bladeCutCnt[blade[I]-1]++;
				bladeCutNo[I]=bladeCutCnt[blade[I]-1];
				bladeIndex[blade[I]-1][bladeCutNo[I]-1]=I+1;
//cout<<"blade["<<I+1<<"]="<<blade[I]<<" BladeCnt="<<BladeCnt<<" bladeCutCnt["<<blade[I]<<"]="
//	<<bladeCutCnt[blade[I]-1]<<" bladeCutNo["<<I+1<<"]="<<bladeCutNo[I]<<"["<<blade[I]-1<<"]["<<bladeCutNo[I]-1<<"]="
//	<<bladeIndex[blade[I]-1][bladeCutNo[I]-1]<<endl;
		}//assign to right value

		return 0;
	} //end arrange
//****************
	int Read_Force95(double F95[200],char ProjName[],int CutNo,char F95_file[])
	{
		double Min,F5,F25,F50,F75,Max;
		ifstream iF95;
		int I,N;
		char dummy_line[200],dummy[20];
		iF95.open (F95_file);		// ics connects to file cs_file
		if (iF95.fail ())
		{
			cerr << "*** ERROR: Cannot open " << F95_file
			<< " for input." << endl;
			cin.ignore();
			cin.ignore();
			return EXIT_FAILURE;	// failure return
		} // end if
		cout<<F95_file<<"  opened for input"<<endl;

		iF95>>dummy>>dummy>>dummy;
		iF95>>ProjName;
		iF95.ignore(120,'\n');
		iF95.getline(dummy_line,200,'\n');
		for (I=0;I<CutNo;I++)
		{
			iF95>>N>>Min>>F5>>F25>>F50>>F75>>F95[CutNo-1-I]>>Max;
			iF95.ignore(80,'\n');
//			cout<<CutNo-I<<" "<<F95[CutNo-1-I]<<endl;
		}
		iF95.close();
		return 0;
	}

	int BldCutMatrixData(int BladeCnt,int bladeCutCnt[200],int bladeIndex[18][30],double doc[200],double Fnc95[200],
		double Ftc95[200],double Ffc95[200],double Knc[200],double Ktc[200],double Kfc[200],double DoH[18][30],
		double FTc[18][30],double FNc[18][30],double FFc[18][30],double KNc[18][30],double KFc[18][30],double KTc[18][30])
	{
		int I,J;
		for (I=0;I<BladeCnt;I++)
		{
			for (J=0;J<bladeCutCnt[I];J++)
			{
				DoH[I][J]=doc[bladeIndex[I][J]-1];
			}
		}

		for (I=0;I<BladeCnt;I++)
		{
			for (J=0;J<bladeCutCnt[I];J++)
			{
				FNc[I][J]=Fnc95[bladeIndex[I][J]-1];
				KNc[I][J]=Knc[bladeIndex[I][J]-1];
				if(KNc[I][J]>=-0.001 && KNc[I][J]<0.001)
				{
					KNc[I][J]=0.001;
				}
				FFc[I][J]=Ffc95[bladeIndex[I][J]-1];
				KFc[I][J]=Kfc[bladeIndex[I][J]-1];
				if(KFc[I][J]>=0.0 && KFc[I][J]<0.001)
				{
					KFc[I][J]=0.001;
				}
				else if(KFc[I][J]<0.0 && KFc[I][J]>-0.001)
				{
					KFc[I][J]=-0.001;
				}
				FTc[I][J]=Ftc95[bladeIndex[I][J]-1];
				KTc[I][J]=Ktc[bladeIndex[I][J]-1];
				if(KTc[I][J]>-0.001 && KTc[I][J]<0.001)
				{
					KTc[I][J]=-0.001;
				}
			}
		}
		return 0;
	}
	int FcutFnFsideMatrixData(int BladeCnt,int bladeCutCnt[200],int bladeIndex[18][30],double Fcut95[200],
		double Fn95[200],double Fside95[200],double FCUT95[18][30],double FN95[18][30],double FSIDE95[18][30])
	{
		int I,J;

		for (I=0;I<BladeCnt;I++)
		{
			for (J=0;J<bladeCutCnt[I];J++)
			{
				FCUT95[I][J]=Fcut95[bladeIndex[I][J]-1];
				FN95[I][J]=Fn95[bladeIndex[I][J]-1];
				FSIDE95[I][J]=Fside95[bladeIndex[I][J]-1];
			}
		}
		return 0;
	} //FnFcutMatrixData
	int Write_SumFile(char sum_file[],char sumB_file[],char sumP_file[],char fcs_file[],double ROPav,double
		tq95,double tqMax,double depthAv[200],int CutNo,int sizeType[],int sizeType0)
	{
		FILE *oSum,*oSumB,*oSumP;//output stream
		int I;
		if ( (oSum=fopen(sum_file, "a"))==NULL)//open output file
		{
			cerr << "*** ERROR: Cannot open " << sum_file
			<< " for output." << endl;
			cin.ignore();
			cin.ignore();
			return EXIT_FAILURE;		// failure return
		} // end if
		cout<<endl;
		cout<<sum_file<<"  opened for output"<<endl;
		fprintf(oSum,fcs_file);
		fprintf(oSum,"  ");
		fprintf(oSum," %7.4f %7.4f  %7.4f ",ROPav, tq95,tqMax);
		if ( (oSumB=fopen(sumB_file, "a"))==NULL)//open output file
		{
			cerr << "*** ERROR: Cannot open " << sumB_file
			<< " for output." << endl;
			cin.ignore();
			cin.ignore();
			return EXIT_FAILURE;		// failure return
		} // end if
		cout<<endl;
		cout<<sumB_file<<"  opened for output"<<endl;
		fprintf(oSumB,fcs_file);
		fprintf(oSumB,"  ");
		fprintf(oSumB," %7.4f %7.4f  %7.4f ",ROPav, tq95,tqMax);
		if ( (oSumP=fopen(sumP_file, "a"))==NULL)//open output file
		{
			cerr << "*** ERROR: Cannot open " << sumP_file
			<< " for output." << endl;
			cin.ignore();
			cin.ignore();
			return EXIT_FAILURE;		// failure return
		} // end if
		cout<<endl;
		cout<<sumP_file<<"  opened for output"<<endl;

		fprintf(oSumP,fcs_file);
		fprintf(oSumP,"  ");
		fprintf(oSumP," %7.4f %7.4f  %7.4f ",ROPav, tq95,tqMax);

		for(I=0;I<CutNo;I++)
			{
				fprintf(oSum,"%6.4f",depthAv[I]);
				fprintf(oSum,"  ");
			}
		fprintf(oSum,"\n");
		fclose(oSum);
		for (I=0;I<CutNo;I++)
		{
			if(sizeType[I]==sizeType0)
			{
				fprintf(oSumB,"%6.4f",depthAv[I]);
				fprintf(oSumB,"  ");
			}
			else
			{
				fprintf(oSumP,"%6.4f",depthAv[I]);
				fprintf(oSumP,"  ");
			}
		}
		fprintf(oSumB,"\n");
		fprintf(oSumP,"\n");

		fclose(oSumB);
		fclose(oSumP);
		return 0;
	}

int Write_FnFcutFside(char FnFcutFside_file[],char FnTitle[],char FcutTitle[],char FsideTitle[],
					  double Fn95[200],double Fcut95[200],double Fside95[200],int CutNo)
	{
		FILE *oFnFcutFside;//output stream
		int I;
		if ( (oFnFcutFside=fopen(FnFcutFside_file, "a"))==NULL)//open output file
		{
			cerr << "*** ERROR: Cannot open " << FnFcutFside_file
			<< " for output." << endl;
			cin.ignore();
			cin.ignore();
			return EXIT_FAILURE;		// failure return
		} // end if
		cout<<endl;
		cout<<FnFcutFside_file<<"  opened for output"<<endl;

		fprintf(oFnFcutFside,FnTitle);
		fprintf(oFnFcutFside,"  ");
		for(I=0;I<CutNo;I++)
		{
			fprintf(oFnFcutFside,"%7.3f",Fn95[I]);
			fprintf(oFnFcutFside,"  ");
		}
		fprintf(oFnFcutFside,"\n");

		fprintf(oFnFcutFside,FcutTitle);
		fprintf(oFnFcutFside,"  ");
		for(I=0;I<CutNo;I++)
		{
			fprintf(oFnFcutFside,"%7.3f",Fcut95[I]);
			fprintf(oFnFcutFside,"  ");
		}
		fprintf(oFnFcutFside,"\n");

		fprintf(oFnFcutFside,FsideTitle);
		fprintf(oFnFcutFside,"  ");
		for(I=0;I<CutNo;I++)
		{
			fprintf(oFnFcutFside,"%7.3f",Fside95[I]);
			fprintf(oFnFcutFside,"  ");
		}
		fprintf(oFnFcutFside,"\n");
		fclose(oFnFcutFside);
		return 0;
	} //end write FcutFnFside

	int Write_fcsFile(char fcs_file[],int cutNum[200],int sizeType[200],int blade[200],int bladeCutNo[200],
		double cutDia[200],double Fnc95[200],double Ftc95[200],double Ffc95[200],double Ftc95bv[200],
		double Fn95[200],double Fcut95[200],double Knc[200],double Ktc[200],double Kfc[200],int CutNo)
	{
	FILE *ofcs;//output stream
	int I;
	if ( (ofcs=fopen(fcs_file, "w"))==NULL)//open output file
	{
		cerr << "*** ERROR: Cannot open " << fcs_file
		<< " for output." << endl;
		cin.ignore();
		cin.ignore();
		return EXIT_FAILURE;		// failure return
	} // end if
	cout<<endl;
	cout<<fcs_file<<"  opened for output"<<endl;

	fprintf(ofcs," cutNo type blade No@Blade cutDia   Fn95    Fcut95   Fnc95   Ftc95   Ffc95  Ftc95bv     Knc       Ktc        Kfc  ");
	fprintf(ofcs,"\n");
	for (I=0;I<CutNo;I++)
	{
		fprintf(ofcs,"%4d %6d %4d %4d",cutNum[I],sizeType[I],blade[I],bladeCutNo[I]);
		fprintf(ofcs,"  ");
//		fprintf(ofcs,"  %7.4f %7.4f",cutDia[I],doc[I]);
		fprintf(ofcs,"  %7.4f ",cutDia[I]);
//		fprintf(ofcs," %7.4f %7.4f %7.4f",Fnc0[I],Ftc0[I],Ffc0[I]);
		fprintf(ofcs," %7.3f %7.3f",Fn95[I],Fcut95[I]);
		fprintf(ofcs,"  ");
		fprintf(ofcs,"%7.3f %7.3f %7.3f %7.3f",Fnc95[I],Ftc95[I],Ffc95[I],Ftc95bv[I]);
		fprintf(ofcs,"  ");
		fprintf(ofcs,"%9.3f %9.3f %9.3f",Knc[I],Ktc[I],Kfc[I]);
		fprintf(ofcs,"\n");
	}
	fclose(ofcs);

	return 0;
	}


	int Bit_DoH(char dohScript[],double doc[200],
		myString Cij[18][30],double DoH[18][30],int BladeCnt,int bladeCutCnt[200],int CutNo)
	{
	FILE *oDOH;//output stream
	int I,J;
	char import1[40]="from abaqus import *";
	char import2[40]="from abaqusConstants import *";
	char import3[40]="from caeModules import *";
	char FileOpen1[]="openMdb(pathName='/data/users/fe9812/084cutter1613/cutter1613_00.cae')";
	char Doh1[]="p = mdb.models['Model-1'].parts['",Doh10[]="']";
	char Doh2[]="p.features['Datum plane-3'].setValues(offset=",Doh20[]=")";
	char Doh3[]="p = mdb.models['Model-1'].parts['",Doh30[]="']";
	char Doh4[]="p.regenerate()";
	char Doh5[]="p = mdb.models['Model-1'].parts['",Doh50[]="']";
	char Doh6[]="p.generateMesh()";
	char Braket[]=")";
	if ( (oDOH=fopen(dohScript, "w"))==NULL)//open output file
	{
		cerr << "*** ERROR: Cannot open " << dohScript
		<< " for output." << endl;
		cin.ignore();
		cin.ignore();
		return EXIT_FAILURE;		// failure return
	} // end if
	cout<<dohScript<<"  opened for output"<<endl;
//	cout<<endl;

	fputs(import1,oDOH);
	fprintf(oDOH,"\n");
	fputs(import2,oDOH);
	fprintf(oDOH,"\n");
	fputs(import3,oDOH);
	fprintf(oDOH,"\n");

	for (I=0;I<BladeCnt;I++)
	{
		for (J=0;J<bladeCutCnt[I];J++)
		{
			fputs(Doh1,oDOH);
			fputs(Cij[I][J].myChar,oDOH);
			fputs(Doh10,oDOH);
			fprintf(oDOH,"\n");

			fputs(Doh2,oDOH);
			fprintf(oDOH,"%5.3f",DoH[I][J]);
			fputs(Doh20,oDOH);
			fprintf(oDOH,"\n");

			fputs(Doh3,oDOH);
			fputs(Cij[I][J].myChar,oDOH);
			fputs(Doh30,oDOH);
			fprintf(oDOH,"\n");

			fputs(Doh4,oDOH);
			fprintf(oDOH,"\n");

			fputs(Doh5,oDOH);
			fputs(Cij[I][J].myChar,oDOH);
			fputs(Doh50,oDOH);
			fprintf(oDOH,"\n");

			fputs(Doh6,oDOH);
			fprintf(oDOH,"\n");

		}
			fprintf(oDOH,"\n");

	}
	fclose(oDOH);
	return 0;
	}

	int Cutter_FcutFnFside_load(char FcutFnFsidePY[],myString FCUTij[18][30],myString FNij[18][30],myString FSIDEij[18][30],
		double FCUT95[18][30],double FN95[18][30],double FSIDE95[18][30],int BladeCnt,int bladeCutCnt[200],int CutNo,
		char ProjName[])
	{
		FILE *iScript;//output stream
		int I,J;
		char import1[40]="from abaqus import *";
		char import2[40]="from abaqusConstants import *";
		char FcutTitle[40]="# Fcut from Project: ";
		char FnTitle[40]="# Fn from Project: ";
		char FsideTitle[40]="# Fside from Project: ";
		char LFcut1[]="mdb.models['Model-1'].loads['";
		char LFcut11[]="'].setValues(cf3=";
		char LFcut12[]=",";
		char LFcut2[]="    distributionType=UNIFORM, field='')";

		char LFn1[]="mdb.models['Model-1'].loads['";
		char LFn11[]="'].setValues(cf1=";
		char LFn12[]=",";
		char LFn2[]="    distributionType=UNIFORM, field='')";

		char LFside1[]="mdb.models['Model-1'].loads['";
		char LFside11[]="'].setValues(cf2=";
		char LFside12[]=",";
		char LFside2[]="    distributionType=UNIFORM, field='')";

		if ( (iScript=fopen(FcutFnFsidePY, "w"))==NULL)//open output file
		{
			cerr << "*** ERROR: Cannot open " << FcutFnFsidePY
			<< " for output." << endl;
			cin.ignore();
			cin.ignore();
			return EXIT_FAILURE;		// failure return
		} // end if
		cout<<FcutFnFsidePY<<"  opened for output"<<endl;
//		cout<<endl;
		fputs(import1,iScript);fprintf(iScript,"\n");
		fputs(import2,iScript);fprintf(iScript,"\n");
		fputs(FcutTitle,iScript);
		fputs(ProjName,iScript);fprintf(iScript,"\n");
		for (I=0;I<BladeCnt;I++)
		{
			for (J=0;J<bladeCutCnt[I];J++)
			{
				fputs(LFcut1,iScript);
				fputs(FCUTij[I][J].myChar,iScript);
				fputs(LFcut11,iScript);
				if(FCUT95[I][J]<0.001)
					{
						FCUT95[I][J]=0.001;
						fprintf(iScript,"%5.3f",-FCUT95[I][J]);
					}
				else if(FCUT95[I][J]<1.0)
					{
						fprintf(iScript,"%5.3f",-FCUT95[I][J]);
					}
				else if(FCUT95[I][J]<10.0)
					{
						fprintf(iScript,"%6.3f",-FCUT95[I][J]);
					}
				else if(FCUT95[I][J]<100.0)
					{
						fprintf(iScript,"%7.3f",-FCUT95[I][J]);
					}
				else
					{
						fprintf(iScript,"%8.3f",-FCUT95[I][J]);
					}
				fputs(LFcut12,iScript);fprintf(iScript,"\n");
				fputs(LFcut2,iScript);fprintf(iScript,"\n");
			}
		}
	//Fn
		fputs(FnTitle,iScript);
		fputs(ProjName,iScript);fprintf(iScript,"\n");
		for (I=0;I<BladeCnt;I++)
		{
			for (J=0;J<bladeCutCnt[I];J++)
			{
				fputs(LFn1,iScript);
				fputs(FNij[I][J].myChar,iScript);
				fputs(LFn11,iScript);
				if(FN95[I][J]<0.001)
					{
						FN95[I][J]=0.001;
						fprintf(iScript,"%5.3f",-FN95[I][J]);
					}
				else if(FN95[I][J]<1.0)
					{
						fprintf(iScript,"%5.3f",-FN95[I][J]);
					}
				else if(FN95[I][J]<10.0)
					{
						fprintf(iScript,"%6.3f",-FN95[I][J]);
					}
				else if(FN95[I][J]<100.0)
					{
						fprintf(iScript,"%7.3f",-FN95[I][J]);
					}
				else
					{
						fprintf(iScript,"%8.3f",-FN95[I][J]);
					}
				fputs(LFn12,iScript);fprintf(iScript,"\n");
				fputs(LFn2,iScript);fprintf(iScript,"\n");
			}

		}
	//Fside
		fputs(FsideTitle,iScript);
		fputs(ProjName,iScript);fprintf(iScript,"\n");
		for (I=0;I<BladeCnt;I++)
		{
			for (J=0;J<bladeCutCnt[I];J++)
			{
				fputs(LFside1,iScript);
				fputs(FSIDEij[I][J].myChar,iScript);
				fputs(LFside11,iScript);
				if(FSIDE95[I][J]<0.001)
					{
						FSIDE95[I][J]=0.001;
						fprintf(iScript,"%5.3f",-FSIDE95[I][J]);
					}
				else if(FSIDE95[I][J]<1.0)
					{
						fprintf(iScript,"%5.3f",-FSIDE95[I][J]);
					}
				else if(FSIDE95[I][J]<10.0)
					{
						fprintf(iScript,"%6.3f",-FSIDE95[I][J]);
					}
				else if(FSIDE95[I][J]<100.0)
					{
						fprintf(iScript,"%7.3f",-FSIDE95[I][J]);
					}
				else
					{
						fprintf(iScript,"%8.3f",-FSIDE95[I][J]);
					}
				fputs(LFside12,iScript);fprintf(iScript,"\n");
				fputs(LFside2,iScript);fprintf(iScript,"\n");
			}

		}

		fclose(iScript);

	return 0;
	}
//endFcutFnFside
	int writePTS_file(char pts_file[15],int CutNo,double radius[200],double angArnd[200],
	double height[200],double prfAng[200],double bkRake[200],double sdRake[200],
	Point3 Point0,Point3 Point[200])
	{
		int I,J;
		double pi=3.141592654;
		double cosF,cosA,cosSR,cosBR,sinF,sinA,sinSR,sinBR;
		double Xij[10],Yij[10],Zij[10];
		for (I=0;I<CutNo;I++)
		{
			cosF=cos(pi/180.0*angArnd[I]);
			cosA=cos(pi/180.0*prfAng[I]);
			cosSR=cos(pi/180.0*sdRake[I]);
			cosBR=cos(pi/180.0*bkRake[I]);
			sinF=sin(pi/180.0*angArnd[I]);
			sinA=sin(pi/180.0*prfAng[I]);
			sinSR=sin(pi/180.0*sdRake[I]);
			sinBR=sin(pi/180.0*bkRake[I]);

			Xij[0]=Point0.X*cosF*cosA*cosSR;
			Xij[1]=Point0.Y*cosF*cosA*sinSR*sinBR;
			Xij[2]=Point0.Y*cosF*sinA*cosBR;
			Xij[3]=Point0.Z*cosF*cosA*sinSR*cosBR;
			Xij[4]=-Point0.Z*cosF*sinA*sinBR;
			Xij[5]=cosF*radius[I];
			Xij[6]=-Point0.X*sinF*sinSR;
			Xij[7]=Point0.Y*sinF*cosSR*sinBR;
			Xij[8]=Point0.Z*sinF*cosSR*cosBR;

			Point[I].X=0.0;
			for (J=0;J<9;J++)
			{
				Point[I].X=Point[I].X+Xij[J];
			}

			Yij[0]=Point0.X*sinF*cosA*cosSR;
			Yij[1]=Point0.Y*sinF*cosA*sinSR*sinBR;
			Yij[2]=Point0.Y*sinF*sinA*cosBR;
			Yij[3]=Point0.Z*sinF*cosA*sinSR*cosBR;
			Yij[4]=-Point0.Z*sinF*sinA*sinBR;
			Yij[5]=sinF*radius[I];
			Yij[6]=Point0.X*cosF*sinSR;
			Yij[7]=-Point0.Y*cosF*cosSR*sinBR;
			Yij[8]=-Point0.Z*cosF*cosSR*cosBR;
			Point[I].Y=0.0;
			for (J=0;J<9;J++)
			{
				Point[I].Y=Point[I].Y+Yij[J];
			}

			Zij[0]=-Point0.X*sinA*cosSR;
			Zij[1]=-Point0.Y*sinA*sinSR*sinBR;
			Zij[2]=Point0.Y*cosA*cosBR;
			Zij[3]=-Point0.Z*sinA*sinSR*cosBR;
			Zij[4]=-Point0.Z*cosA*sinBR;
			Zij[5]=height[I];
			Point[I].Z=0.0;
			for (J=0;J<6;J++)
			{
				Point[I].Z=Point[I].Z+Zij[J];
			}
		}
/*		if ( (opts=fopen(pts_file, "w"))==NULL)//open output file
		{
			cerr << "*** ERROR: Cannot open " << pts_file
			<< " for output." << endl;
			cin.ignore();
			cin.ignore();
			return EXIT_FAILURE;		// failure return
		} // end if
		cout<<pts_file<<"  opened for output"<<endl;
//		cout<<endl;
		for (I=0;I<CutNo;I++)
		{
			fprintf(opts," %7.4f %7.4f %7.4f",Point[I].X,Point[I].Y,Point[I].Z);
			fprintf(opts,"  ");
			fprintf(opts,"\n");
		}
		fclose(opts);*/
		return 0;
	} //end pts file
int writePTS_file_ptNew(char pts_file[15],int CutNo,double radius[200],double angArnd[200],double cutLen[200],
	double height[200],double prfAng[200],double bkRake[200],double sdRake[200],double cutDia[200],
	Point3 Point[200],double pocket_oversize) //find center point coordinates of pocket face
	{
		FILE *opts;//output stream
		int I,J;
		double pi=3.141592654;
		double cosF,cosA,cosSR,cosBR,sinF,sinA,sinSR,sinBR;
		double Xij[10],Yij[10],Zij[10];
		Point3 Pointo[200];
		for (I=0;I<CutNo;I++)
		{
			cosF=cos(pi/180.0*angArnd[I]);
			cosA=cos(pi/180.0*prfAng[I]);
			cosSR=cos(pi/180.0*sdRake[I]);
			cosBR=cos(pi/180.0*bkRake[I]);
			sinF=sin(pi/180.0*angArnd[I]);
			sinA=sin(pi/180.0*prfAng[I]);
			sinSR=sin(pi/180.0*sdRake[I]);
			sinBR=sin(pi/180.0*bkRake[I]);
			if(bkRake[I]>0.01)
			{
				Pointo[I].X=0.0;Pointo[I].Y=-cutDia[I]/2.0;Pointo[I].Z=cutLen[I]+pocket_oversize/2.0;
			}
			else
			{
				Pointo[I].X=0.0;Pointo[I].Y=-cutLen[I]-pocket_oversize/2.0;Pointo[I].Z=0.0;
			}

			Xij[0]=Pointo[I].X*cosF*cosA*cosSR;
			Xij[1]=Pointo[I].Y*cosF*cosA*sinSR*sinBR;
			Xij[2]=Pointo[I].Y*cosF*sinA*cosBR;
			Xij[3]=Pointo[I].Z*cosF*cosA*sinSR*cosBR;
			Xij[4]=-Pointo[I].Z*cosF*sinA*sinBR;
			Xij[5]=cosF*radius[I];
			Xij[6]=-Pointo[I].X*sinF*sinSR;
			Xij[7]=Pointo[I].Y*sinF*cosSR*sinBR;
			Xij[8]=Pointo[I].Z*sinF*cosSR*cosBR;

			Point[I].X=0.0;
			for (J=0;J<9;J++)
			{
				Point[I].X=Point[I].X+Xij[J];
			}

			Yij[0]=Pointo[I].X*sinF*cosA*cosSR;
			Yij[1]=Pointo[I].Y*sinF*cosA*sinSR*sinBR;
			Yij[2]=Pointo[I].Y*sinF*sinA*cosBR;
			Yij[3]=Pointo[I].Z*sinF*cosA*sinSR*cosBR;
			Yij[4]=-Pointo[I].Z*sinF*sinA*sinBR;
			Yij[5]=sinF*radius[I];
			Yij[6]=Pointo[I].X*cosF*sinSR;
			Yij[7]=-Pointo[I].Y*cosF*cosSR*sinBR;
			Yij[8]=-Pointo[I].Z*cosF*cosSR*cosBR;
			Point[I].Y=0.0;
			for (J=0;J<9;J++)
			{
				Point[I].Y=Point[I].Y+Yij[J];
			}

			Zij[0]=-Pointo[I].X*sinA*cosSR;
			Zij[1]=-Pointo[I].Y*sinA*sinSR*sinBR;
			Zij[2]=Pointo[I].Y*cosA*cosBR;
			Zij[3]=-Pointo[I].Z*sinA*sinSR*cosBR;
			Zij[4]=-Pointo[I].Z*cosA*sinBR;
			Zij[5]=height[I];
			Point[I].Z=0.0;
			for (J=0;J<6;J++)
			{
				Point[I].Z=Point[I].Z+Zij[J];
			}
		}
/*		if ( (opts=fopen(pts_file, "w"))==NULL)//open output file
		{
			cerr << "*** ERROR: Cannot open " << pts_file
			<< " for output." << endl;
			cin.ignore();
			cin.ignore();
			return EXIT_FAILURE;		// failure return
		} // end if
		cout<<pts_file<<"  opened for output"<<endl;
//		cout<<endl;
		for (I=0;I<CutNo;I++)
		{
			fprintf(opts," %9.6f %9.6f %9.6f",Point[I].X,Point[I].Y,Point[I].Z);
			fprintf(opts,"  ");
			fprintf(opts,"\n");
		}
		fclose(opts);*/
		return 0;
	} //end pocket pts file New
int writePTS_file_PcylBtm_pt(char pts_file[15],int CutNo,double radius[200],double angArnd[200],double cutLen[200],
	double height[200],double prfAng[200],double bkRake[200],double sdRake[200],double cutDia[200],
	Point3 Point[200],double pocket_oversize) //find center point coordinates of bottom cylinder face
	{
		FILE *opts;//output stream
		int I,J;
		double pi=3.141592654;
		double cosF,cosA,cosSR,cosBR,sinF,sinA,sinSR,sinBR;
		double Xij[10],Yij[10],Zij[10];
		Point3 Pointo[200];
		for (I=0;I<CutNo;I++)
		{
			cosF=cos(pi/180.0*angArnd[I]);
			cosA=cos(pi/180.0*prfAng[I]);
			cosSR=cos(pi/180.0*sdRake[I]);
			cosBR=cos(pi/180.0*bkRake[I]);
			sinF=sin(pi/180.0*angArnd[I]);
			sinA=sin(pi/180.0*prfAng[I]);
			sinSR=sin(pi/180.0*sdRake[I]);
			sinBR=sin(pi/180.0*bkRake[I]);
			if(bkRake[I]>0.01)
			{
				Pointo[I].X=0.0;Pointo[I].Y=-cutDia[I]/2.0;Pointo[I].Z=cutLen[I]+0.01;
			}
			else
			{
				Pointo[I].X=0.0;Pointo[I].Y=-cutLen[I]-0.01;Pointo[I].Z=0.0;
			}

			Xij[0]=Pointo[I].X*cosF*cosA*cosSR;
			Xij[1]=Pointo[I].Y*cosF*cosA*sinSR*sinBR;
			Xij[2]=Pointo[I].Y*cosF*sinA*cosBR;
			Xij[3]=Pointo[I].Z*cosF*cosA*sinSR*cosBR;
			Xij[4]=-Pointo[I].Z*cosF*sinA*sinBR;
			Xij[5]=cosF*radius[I];
			Xij[6]=-Pointo[I].X*sinF*sinSR;
			Xij[7]=Pointo[I].Y*sinF*cosSR*sinBR;
			Xij[8]=Pointo[I].Z*sinF*cosSR*cosBR;

			Point[I].X=0.0;
			for (J=0;J<9;J++)
			{
				Point[I].X=Point[I].X+Xij[J];
			}

			Yij[0]=Pointo[I].X*sinF*cosA*cosSR;
			Yij[1]=Pointo[I].Y*sinF*cosA*sinSR*sinBR;
			Yij[2]=Pointo[I].Y*sinF*sinA*cosBR;
			Yij[3]=Pointo[I].Z*sinF*cosA*sinSR*cosBR;
			Yij[4]=-Pointo[I].Z*sinF*sinA*sinBR;
			Yij[5]=sinF*radius[I];
			Yij[6]=Pointo[I].X*cosF*sinSR;
			Yij[7]=-Pointo[I].Y*cosF*cosSR*sinBR;
			Yij[8]=-Pointo[I].Z*cosF*cosSR*cosBR;
			Point[I].Y=0.0;
			for (J=0;J<9;J++)
			{
				Point[I].Y=Point[I].Y+Yij[J];
			}

			Zij[0]=-Pointo[I].X*sinA*cosSR;
			Zij[1]=-Pointo[I].Y*sinA*sinSR*sinBR;
			Zij[2]=Pointo[I].Y*cosA*cosBR;
			Zij[3]=-Pointo[I].Z*sinA*sinSR*cosBR;
			Zij[4]=-Pointo[I].Z*cosA*sinBR;
			Zij[5]=height[I];
			Point[I].Z=0.0;
			for (J=0;J<6;J++)
			{
				Point[I].Z=Point[I].Z+Zij[J];
			}
		}
/*		if ( (opts=fopen(pts_file, "w"))==NULL)//open output file
		{
			cerr << "*** ERROR: Cannot open " << pts_file
			<< " for output." << endl;
			cin.ignore();
			cin.ignore();
			return EXIT_FAILURE;		// failure return
		} // end if
		cout<<pts_file<<"  opened for output"<<endl;
//		cout<<endl;
		for (I=0;I<CutNo;I++)
		{
			fprintf(opts," %9.6f %9.6f %9.6f",Point[I].X,Point[I].Y,Point[I].Z);
			fprintf(opts,"  ");
			fprintf(opts,"\n");
		}
		fclose(opts);*/
		return 0;
	} //end pocket pts file New//*find pocket btm point
int writePTS_file_PcylTop_pt(char pts_file[15],int CutNo,double radius[200],double angArnd[200],double cutLen[200],
	double height[200],double prfAng[200],double bkRake[200],double sdRake[200],double cutDia[200],
	Point3 Point[200],double pocket_oversize) //find center point coordinates of bottom cylinder face
	{
		FILE *opts;//output stream
		int I,J;
		double pi=3.141592654;
		double cosF,cosA,cosSR,cosBR,sinF,sinA,sinSR,sinBR;
		double Xij[10],Yij[10],Zij[10];
		Point3 Pointo[200];
		for (I=0;I<CutNo;I++)
		{
			cosF=cos(pi/180.0*angArnd[I]);
			cosA=cos(pi/180.0*prfAng[I]);
			cosSR=cos(pi/180.0*sdRake[I]);
			cosBR=cos(pi/180.0*bkRake[I]);
			sinF=sin(pi/180.0*angArnd[I]);
			sinA=sin(pi/180.0*prfAng[I]);
			sinSR=sin(pi/180.0*sdRake[I]);
			sinBR=sin(pi/180.0*bkRake[I]);
			if(bkRake[I]>0.01)
			{
				Pointo[I].X=0.0;Pointo[I].Y=-cutDia[I]/2.0;Pointo[I].Z=-0.1;
			}
			else
			{
				Pointo[I].X=0.0;Pointo[I].Y=0.1;Pointo[I].Z=0.0;
			}

			Xij[0]=Pointo[I].X*cosF*cosA*cosSR;
			Xij[1]=Pointo[I].Y*cosF*cosA*sinSR*sinBR;
			Xij[2]=Pointo[I].Y*cosF*sinA*cosBR;
			Xij[3]=Pointo[I].Z*cosF*cosA*sinSR*cosBR;
			Xij[4]=-Pointo[I].Z*cosF*sinA*sinBR;
			Xij[5]=cosF*radius[I];
			Xij[6]=-Pointo[I].X*sinF*sinSR;
			Xij[7]=Pointo[I].Y*sinF*cosSR*sinBR;
			Xij[8]=Pointo[I].Z*sinF*cosSR*cosBR;

			Point[I].X=0.0;
			for (J=0;J<9;J++)
			{
				Point[I].X=Point[I].X+Xij[J];
			}

			Yij[0]=Pointo[I].X*sinF*cosA*cosSR;
			Yij[1]=Pointo[I].Y*sinF*cosA*sinSR*sinBR;
			Yij[2]=Pointo[I].Y*sinF*sinA*cosBR;
			Yij[3]=Pointo[I].Z*sinF*cosA*sinSR*cosBR;
			Yij[4]=-Pointo[I].Z*sinF*sinA*sinBR;
			Yij[5]=sinF*radius[I];
			Yij[6]=Pointo[I].X*cosF*sinSR;
			Yij[7]=-Pointo[I].Y*cosF*cosSR*sinBR;
			Yij[8]=-Pointo[I].Z*cosF*cosSR*cosBR;
			Point[I].Y=0.0;
			for (J=0;J<9;J++)
			{
				Point[I].Y=Point[I].Y+Yij[J];
			}

			Zij[0]=-Pointo[I].X*sinA*cosSR;
			Zij[1]=-Pointo[I].Y*sinA*sinSR*sinBR;
			Zij[2]=Pointo[I].Y*cosA*cosBR;
			Zij[3]=-Pointo[I].Z*sinA*sinSR*cosBR;
			Zij[4]=-Pointo[I].Z*cosA*sinBR;
			Zij[5]=height[I];
			Point[I].Z=0.0;
			for (J=0;J<6;J++)
			{
				Point[I].Z=Point[I].Z+Zij[J];
			}
		}
/*		if ( (opts=fopen(pts_file, "w"))==NULL)//open output file
		{
			cerr << "*** ERROR: Cannot open " << pts_file
			<< " for output." << endl;
			cin.ignore();
			cin.ignore();
			return EXIT_FAILURE;		// failure return
		} // end if
		cout<<pts_file<<"  opened for output"<<endl;
//		cout<<endl;
		for (I=0;I<CutNo;I++)
		{
			fprintf(opts," %9.6f %9.6f %9.6f",Point[I].X,Point[I].Y,Point[I].Z);
			fprintf(opts,"  ");
			fprintf(opts,"\n");
		}
		fclose(opts);*/
		return 0;
	} //end pocket pts file New//*find pocket top point
int AssignPocketSetFaceByBoundingCylinder(char pocket_faceset_file[30],myString Pij[18][30],int BladeCnt,int bladeCutCnt[200],
	Point3 PcylBtmBij[18][30],Point3 PcylTopBij[18][30],double cutDia[200],int bladeIndex[18][30],double bottom1,double bottom2,double bottom3,
	double top1,double top2,double top3,double bodyDia1,double bodyDia2,double bodyDia3)
	{
		//data for 3-points coordinates
		int I,J;
		//normal condition
		FILE *ocys;//output stream
		char import1[]="from abaqus import *";
		char import2[]="from abaqusConstants import *";
		char import3[]="from caeModules import *";
		char Line00[]="p = mdb.models['Model-1'].parts['bitbody']";
		char Line01[]="s = p.faces";

		char Line0[]="#";
		char Line1[]="sdFaces1 = s.getByBoundingCylinder((";
		char Line11[]=",";
		char Line12[]=",";
		char Line13[]="),";
		char Line2[]="(";
		char Line21[]=",";
		char Line22[]=",";
		char Line23[]="),";
		char Line24[]=")";
		char Line30[]="p.Surface(side1Faces=sdFaces1, name='";
		char Line310[]="')";
		char Line3[]="p.Set(faces=sdFaces1, name='";
		char Line31[]="')";

		char Line32[]="#merge_pocket_face_set";
		char Line33[]="p.SetByBoolean(name='PocketFaces',sets=(";
		char Line35[]="    p.sets['";
		char Line351[]="'],";
		char Line36[]=" ))";

//for face_set
		char Line03[]="#set1";
		char Line04[]="faces = s.getByBoundingCylinder((0.0,0.0,";
		char Line041[]="),";
		char Line05[]="(0.0,0.0,";
		char Line051[]="),";
		char Line052[]=")";
		char Line06[]="p.Set(faces=faces, name='body_face1')";
		char Line07[]="#set2";
		char Line08[]="faces = s.getByBoundingCylinder((0.0,0.0,";
		char Line081[]="),";
		char Line09[]="(0.0,0.0,";
		char Line091[]="),";
		char Line092[]=")";
		char Line10[]="p.Set(faces=faces, name='body_face2')";
		char Line107[]="#set3";
		char Line108[]="faces = s.getByBoundingCylinder((0.0,0.0,";
		char Line1081[]="),";
		char Line109[]="(0.0,0.0,";
		char Line1091[]="),";
		char Line1092[]=")";
		char Line110[]="p.Set(faces=faces, name='body_face3')";
		char Line011[]="#merge_sets";
		char Line012[]="p.SetByBoolean(name='body_face', operation=DIFFERENCE, sets=(";
		char Line013[]="    p.sets['body_face1'], p.sets['body_face2'],";
		char Line0113[]="    p.sets['body_face3'], p.sets['PocketFaces'], ))";

	if ((ocys=fopen(pocket_faceset_file, "w"))==NULL)//open output file
		{
			cerr << "*** ERROR: Cannot open " << pocket_faceset_file
			<< " for output." << endl;
			cin.ignore();
			cin.ignore();
			return EXIT_FAILURE;		// failure return
		} // end if
		cout<<pocket_faceset_file<<"  opened for output"<<endl;
		cout<<endl;
		fputs(import1,ocys);fprintf(ocys,"\n");
		fputs(import2,ocys);fprintf(ocys,"\n");
		fputs(import3,ocys);fprintf(ocys,"\n");
		fprintf(ocys,"\n");
		fputs(Line00,ocys);fprintf(ocys,"\n");
		fputs(Line01,ocys);fprintf(ocys,"\n");
		fprintf(ocys,"\n");
		for (I=0;I<BladeCnt;I++)
		{
			for (J=0;J<bladeCutCnt[I];J++)
			{
				fputs(Line0,ocys);
				fputs(Pij[I][J].myChar,ocys);fprintf(ocys,"\n");
				fputs(Line1,ocys);
				fprintf(ocys,"%9.6f",PcylBtmBij[I][J].X);
				fputs(Line11,ocys);
				fprintf(ocys,"%9.6f",PcylBtmBij[I][J].Y);
				fputs(Line12,ocys);
				fprintf(ocys,"%9.6f",PcylBtmBij[I][J].Z);
				fputs(Line13,ocys);fprintf(ocys,"\n");
				fputs(Line2,ocys);;
				fprintf(ocys,"%9.6f",PcylTopBij[I][J].X);
				fputs(Line21,ocys);
				fprintf(ocys,"%9.6f",PcylTopBij[I][J].Y);
				fputs(Line22,ocys);
				fprintf(ocys,"%9.6f",PcylTopBij[I][J].Z);
				fputs(Line23,ocys);
				fprintf(ocys,"%6.4f",cutDia[bladeIndex[I][J]-1]/2.0+0.01);
				fputs(Line24,ocys);fprintf(ocys,"\n");
				//fputs(Line30,ocys);
				//fputs(Pij[I][J].myChar,ocys);
				//fputs(Line310,ocys);fprintf(ocys,"\n");
				fputs(Line3,ocys);
				fputs(Pij[I][J].myChar,ocys);
				fputs(Line31,ocys);fprintf(ocys,"\n");
			}
		}
		fputs(Line32,ocys);fprintf(ocys,"\n");
		fputs(Line33,ocys);fprintf(ocys,"\n");
		for (I=0;I<BladeCnt;I++)
		{
			for (J=0;J<bladeCutCnt[I];J++)
			{
				fputs(Line35,ocys);
				fputs(Pij[I][J].myChar,ocys);
				fputs(Line351,ocys);fprintf(ocys,"\n");
			}
		}
		fputs(Line36,ocys);fprintf(ocys,"\n");
//for body_face
		fputs(Line00,ocys);fprintf(ocys,"\n");
		fputs(Line01,ocys);fprintf(ocys,"\n");
//sets
		fputs(Line03,ocys);fprintf(ocys,"\n");
		fputs(Line04,ocys);
		fprintf(ocys,"%4.2f",bottom1);
		fputs(Line041,ocys);fprintf(ocys,"\n");
		fputs(Line05,ocys);
		fprintf(ocys,"%4.2f",top1);
		fputs(Line051,ocys);
		fprintf(ocys,"%4.2f",bodyDia1/2.0);
		fputs(Line052,ocys);fprintf(ocys,"\n");
		fputs(Line06,ocys);fprintf(ocys,"\n");
//set2
		fputs(Line07,ocys);fprintf(ocys,"\n");
		fputs(Line08,ocys);
		fprintf(ocys,"%4.2f",bottom2);
		fputs(Line081,ocys);fprintf(ocys,"\n");
		fputs(Line09,ocys);
		fprintf(ocys,"%4.2f",top2);
		fputs(Line091,ocys);
		fprintf(ocys,"%4.2f",bodyDia2/2.0);
		fputs(Line092,ocys);fprintf(ocys,"\n");
		fputs(Line10,ocys);fprintf(ocys,"\n");
//set3
		fputs(Line107,ocys);fprintf(ocys,"\n");
		fputs(Line108,ocys);
		fprintf(ocys,"%4.2f",bottom3);
		fputs(Line1081,ocys);fprintf(ocys,"\n");
		fputs(Line109,ocys);
		fprintf(ocys,"%4.2f",top3);
		fputs(Line1091,ocys);
		fprintf(ocys,"%4.2f",bodyDia3/2.0);
		fputs(Line1092,ocys);fprintf(ocys,"\n");
		fputs(Line110,ocys);fprintf(ocys,"\n");
//merge sets
		fputs(Line011,ocys);fprintf(ocys,"\n");
		fputs(Line012,ocys);fprintf(ocys,"\n");
		fputs(Line013,ocys);fprintf(ocys,"\n");
		fputs(Line0113,ocys);fprintf(ocys,"\n");
		fclose(ocys);
		return 0;
	} //end AssignPocketSetFaceByBoundingCylinder//******

int writePTS_file_side_ptNew(char pts_file[15],int CutNo,double radius[200],double angArnd[200],double cutLen[200],
	double height[200],double prfAng[200],double bkRake[200],double sdRake[200],double cutDia[200],
	Point3 Point[200],double pocket_oversize) //find side point coordinates of pocket face
	{
		FILE *opts;//output stream
		int I,J;
		double pi=3.141592654;
		double cosF,cosA,cosSR,cosBR,sinF,sinA,sinSR,sinBR;
		double Xij[10],Yij[10],Zij[10];
		Point3 Pointo[200];
		for (I=0;I<CutNo;I++)
		{
			cosF=cos(pi/180.0*angArnd[I]);
			cosA=cos(pi/180.0*prfAng[I]);
			cosSR=cos(pi/180.0*sdRake[I]);
			cosBR=cos(pi/180.0*bkRake[I]);
			sinF=sin(pi/180.0*angArnd[I]);
			sinA=sin(pi/180.0*prfAng[I]);
			sinSR=sin(pi/180.0*sdRake[I]);
			sinBR=sin(pi/180.0*bkRake[I]);

/*			if(bkRake[I]>0.01)
			{
				Pointo[I].X=0.0;
				Pointo[I].Y=-cutDia[I]-pocket_oversize/2.0;
				Pointo[I].Z=cutLen[I]+pocket_oversize/2.0-0.05;
			}
			else
			{
				Pointo[I].X=0.0;
				Pointo[I].Y=-cutLen[I]-pocket_oversize/2.0+0.05;
				Pointo[I].Z=-cutDia[I]/2.0-pocket_oversize/2.0;
			}*/
			if(bkRake[I]>0.01)
			{
				Pointo[I].X=-cutDia[I]/2.0-pocket_oversize/2.0;
				Pointo[I].Y=-cutDia[I]/2.0;
				Pointo[I].Z=cutLen[I]+pocket_oversize/2.0-0.05;
			}
			else
			{
				Pointo[I].X=-cutDia[I]/2.0-pocket_oversize/2.0;
				Pointo[I].Y=-cutLen[I]-pocket_oversize/2.0+0.05;
				Pointo[I].Z=0.0;
			}

			Xij[0]=Pointo[I].X*cosF*cosA*cosSR;
			Xij[1]=Pointo[I].Y*cosF*cosA*sinSR*sinBR;
			Xij[2]=Pointo[I].Y*cosF*sinA*cosBR;
			Xij[3]=Pointo[I].Z*cosF*cosA*sinSR*cosBR;
			Xij[4]=-Pointo[I].Z*cosF*sinA*sinBR;
			Xij[5]=cosF*radius[I];
			Xij[6]=-Pointo[I].X*sinF*sinSR;
			Xij[7]=Pointo[I].Y*sinF*cosSR*sinBR;
			Xij[8]=Pointo[I].Z*sinF*cosSR*cosBR;

			Point[I].X=0.0;
			for (J=0;J<9;J++)
			{
				Point[I].X=Point[I].X+Xij[J];
			}

			Yij[0]=Pointo[I].X*sinF*cosA*cosSR;
			Yij[1]=Pointo[I].Y*sinF*cosA*sinSR*sinBR;
			Yij[2]=Pointo[I].Y*sinF*sinA*cosBR;
			Yij[3]=Pointo[I].Z*sinF*cosA*sinSR*cosBR;
			Yij[4]=-Pointo[I].Z*sinF*sinA*sinBR;
			Yij[5]=sinF*radius[I];
			Yij[6]=Pointo[I].X*cosF*sinSR;
			Yij[7]=-Pointo[I].Y*cosF*cosSR*sinBR;
			Yij[8]=-Pointo[I].Z*cosF*cosSR*cosBR;
			Point[I].Y=0.0;
			for (J=0;J<9;J++)
			{
				Point[I].Y=Point[I].Y+Yij[J];
			}

			Zij[0]=-Pointo[I].X*sinA*cosSR;
			Zij[1]=-Pointo[I].Y*sinA*sinSR*sinBR;
			Zij[2]=Pointo[I].Y*cosA*cosBR;
			Zij[3]=-Pointo[I].Z*sinA*sinSR*cosBR;
			Zij[4]=-Pointo[I].Z*cosA*sinBR;
			Zij[5]=height[I];
			Point[I].Z=0.0;
			for (J=0;J<6;J++)
			{
				Point[I].Z=Point[I].Z+Zij[J];
			}
		}
/*		if ( (opts=fopen(pts_file, "w"))==NULL)//open output file
		{
			cerr << "*** ERROR: Cannot open " << pts_file
			<< " for output." << endl;
			cin.ignore();
			cin.ignore();
			return EXIT_FAILURE;		// failure return
		} // end if
		cout<<pts_file<<"  opened for output"<<endl;
//		cout<<endl;
		for (I=0;I<CutNo;I++)
		{
			fprintf(opts," %9.6f %9.6f %9.6f",Point[I].X,Point[I].Y,Point[I].Z);
			fprintf(opts,"  ");
			fprintf(opts,"\n");
		}
		fclose(opts);*/
		return 0;
	} //end side pts file New
//end side point

//end side point
int writeCordPts_file(char CordPts_file[15],int CutNo,Point3 Pointo[200],Point3 Pointx[200],Point3 Pointy[200])
	{
		FILE *ocords;//output stream
		int I;
		if ( (ocords=fopen(CordPts_file, "w"))==NULL)//open output file
		{
			cerr << "*** ERROR: Cannot open " << CordPts_file
			<< " for output." << endl;
			cin.ignore();
			cin.ignore();
			return EXIT_FAILURE;		// failure return
		} // end if
		cout<<CordPts_file<<"  opened for output"<<endl;
//		cout<<endl;
		for (I=0;I<CutNo;I++)
		{
			fprintf(ocords,"%-4d",I+1);
//			fprintf(ocords,"\t");
			fprintf(ocords," %7.4f %7.4f %7.4f",Pointo[I].X,Pointo[I].Y,Pointo[I].Z);
			fprintf(ocords," %7.4f %7.4f %7.4f",Pointx[I].X,Pointx[I].Y,Pointx[I].Z);
			fprintf(ocords," %7.4f %7.4f %7.4f",Pointy[I].X,Pointy[I].Y,Pointy[I].Z);
			fprintf(ocords,"\n");
		}
		fclose(ocords);
		return 0;
	} //end cord_pro

int BldPtsMatrixData(char ptsBij_file[15],int BladeCnt,int bladeCutCnt[200],int bladeIndex[18][30],
		Point3 Po[200],Point3 Px[200],Point3 Py[200],
		Point3 PoBij[18][30],Point3 PxBij[18][30],Point3 PyBij[18][30])//change order to blade by blade
	{
		int I,J;

		for (I=0;I<BladeCnt;I++)
		{
			for (J=0;J<bladeCutCnt[I];J++)
			{
				PoBij[I][J].X=Po[bladeIndex[I][J]-1].X;
				PoBij[I][J].Y=Po[bladeIndex[I][J]-1].Y;
				PoBij[I][J].Z=Po[bladeIndex[I][J]-1].Z;
			}
		}
		for (I=0;I<BladeCnt;I++)
		{
			for (J=0;J<bladeCutCnt[I];J++)
			{
				PxBij[I][J].X=Px[bladeIndex[I][J]-1].X;
				PxBij[I][J].Y=Px[bladeIndex[I][J]-1].Y;
				PxBij[I][J].Z=Px[bladeIndex[I][J]-1].Z;
			}
		}
		for (I=0;I<BladeCnt;I++)
		{
			for (J=0;J<bladeCutCnt[I];J++)
			{
				PyBij[I][J].X=Py[bladeIndex[I][J]-1].X;
				PyBij[I][J].Y=Py[bladeIndex[I][J]-1].Y;
				PyBij[I][J].Z=Py[bladeIndex[I][J]-1].Z;
			}
		}
/*		if ( (opts=fopen(ptsBij_file, "w"))==NULL)//open output file
		{
			cerr << "*** ERROR: Cannot open " << ptsBij_file
			<< " for output." << endl;
			cin.ignore();
			cin.ignore();
			return EXIT_FAILURE;		// failure return
		} // end if

		cout<<ptsBij_file<<"  opened for output"<<endl;
//		cout<<endl;
		for (I=0;I<BladeCnt;I++)
		{
			for (J=0;J<bladeCutCnt[I];J++)
			{
			fprintf(opts," %7.4f %7.4f %7.4f",PoBij[I][J].X,PoBij[I][J].Y,PoBij[I][J].Z);
			fprintf(opts,"\n");
			}
		}
		for (I=0;I<BladeCnt;I++)
		{
			for (J=0;J<bladeCutCnt[I];J++)
			{
			fprintf(opts," %7.4f %7.4f %7.4f",PxBij[I][J].X,PxBij[I][J].Y,PxBij[I][J].Z);
			fprintf(opts,"\n");
			}
		}
		for (I=0;I<BladeCnt;I++)
		{
			for (J=0;J<bladeCutCnt[I];J++)
			{
			fprintf(opts," %7.4f %7.4f %7.4f",PyBij[I][J].X,PyBij[I][J].Y,PyBij[I][J].Z);
			fprintf(opts,"\n");
			}
		}
		fclose(opts);*/
		return 0;
	}


int WriteAssignCordsPS(char cordcspy_file[],myString CSij[18][30],myString Pij[18][30],int BladeCnt,
				int bladeCutCnt[200],Point3 PoBij[18][30],Point3 PxBij[18][30],Point3 PyBij[18][30])
	{
		//data for 3-points coordinates
		int I,J;
		//normal condition
		FILE *ocys;//output stream
		char import1[]="from abaqus import *";
		char import2[]="from abaqusConstants import *";
		char import3[]="from caeModules import *";
		char Line00[]="p = mdb.models['Model-1'].parts['bitbody']";


		char Line0[]="#";
		char Line1[]="p.DatumCsysByThreePoints(name='";
		char Line11[]="', coordSysType=CARTESIAN, origin=(";
		char Line12[]=",";
		char Line2[]="   ";
		char Line21[]=", ";
		char Line22[]="), point1=(";
		char Line23[]=", ";
		char Line24[]=", ";
		char Line25[]="), point2=(";
		char Line26[]=", ";
		char Line27[]=", ";
		char Line28[]="))";
		//assign data
//for uniCys2
	if ((ocys=fopen(cordcspy_file, "w"))==NULL)//open output file
		{
			cerr << "*** ERROR: Cannot open " << cordcspy_file
			<< " for output." << endl;
			cin.ignore();
			cin.ignore();
			return EXIT_FAILURE;		// failure return
		} // end if
		cout<<cordcspy_file<<"  opened for output"<<endl;
//		cout<<endl;
		fputs(import1,ocys);
		fprintf(ocys,"\n");
		fputs(import2,ocys);
		fprintf(ocys,"\n");
		fputs(import3,ocys);
		fprintf(ocys,"\n");
		fprintf(ocys,"\n");
		fputs(Line00,ocys);
		fprintf(ocys,"\n");
		fprintf(ocys,"\n");
		for (I=0;I<BladeCnt;I++)
		{
			for (J=0;J<bladeCutCnt[I];J++)
			{
				fputs(Line0,ocys);
				fputs(Pij[I][J].myChar,ocys);fprintf(ocys,"\n");
				fputs(CSij[I][J].myChar,ocys);fprintf(ocys,"=");
				fputs(Line1,ocys);
				fputs(Pij[I][J].myChar,ocys);
				fputs(Line11,ocys);
				fprintf(ocys,"%6.4f",PoBij[I][J].X);
				fputs(Line12,ocys);fprintf(ocys,"\n");
				fputs(Line2,ocys);
				fprintf(ocys,"%6.4f",PoBij[I][J].Y);
				fputs(Line21,ocys);
				fprintf(ocys,"%6.4f",PoBij[I][J].Z);
				fputs(Line22,ocys);
				fprintf(ocys,"%6.4f",PxBij[I][J].X);
				fputs(Line23,ocys);
				fprintf(ocys,"%6.4f",PxBij[I][J].Y);
				fputs(Line24,ocys);
				fprintf(ocys,"%6.4f",PxBij[I][J].Z);
				fputs(Line25,ocys);
				fprintf(ocys,"%6.4f",PyBij[I][J].X);
				fputs(Line26,ocys);
				fprintf(ocys,"%6.4f",PyBij[I][J].Y);
				fputs(Line27,ocys);
				fprintf(ocys,"%6.4f",PyBij[I][J].Z);
				fputs(Line28,ocys);fprintf(ocys,"\n");
			}
		}
		fclose(ocys);
		return 0;
	} //end cord2
//reference point start
int WriteAssignRPsPS(char rpspy_file[],myString RPSij[18][30],myString RPij[18][30],myString setRPij[18][30],
					 int BladeCnt,int bladeCutCnt[200],Point3 PoBij[18][30])
	{
		//data for 3-points coordinates
		int I,J;
		//normal condition
		FILE *ocys;//output stream
		char import1[]="from abaqus import *";
		char import2[]="from abaqusConstants import *";
		char import3[]="from caeModules import *";
		char Line00[]="a = mdb.models['Model-1'].rootAssembly";


		char Line0[]="#";
		char Line1[]="=a.ReferencePoint(point=(";
		char Line11[]=", ";
		char Line12[]=", ";
		char Line13[]="))";
		char Line2[]="mdb.models['Model-1'].rootAssembly.features.changeKey(fromName='RP-1',";
		char Line3[]="    toName='";
		char Line31[]="')";
		char Line4[]="r1 = a.referencePoints";
		char Line5[]="refPoints1=(r1[";
		char Line51[]=".id], )";
		char Line6[]="a.Set(referencePoints=refPoints1, name='";
		char Line61[]="')";
		char Line25[]="), point2=(";
		char Line26[]=", ";
		char Line27[]=", ";
		char Line28[]="))";

		//assign data
//for uniCys2
	if ((ocys=fopen(rpspy_file, "w"))==NULL)//open output file
		{
			cerr << "*** ERROR: Cannot open " << rpspy_file
			<< " for output." << endl;
			cin.ignore();
			cin.ignore();
			return EXIT_FAILURE;		// failure return
		} // end if
		cout<<rpspy_file<<"  opened for output"<<endl;
//		cout<<endl;
		fputs(import1,ocys);
		fprintf(ocys,"\n");
		fputs(import2,ocys);
		fprintf(ocys,"\n");
		fputs(import3,ocys);
		fprintf(ocys,"\n");
		fprintf(ocys,"\n");
		fputs(Line00,ocys);
		fprintf(ocys,"\n");
		fprintf(ocys,"\n");
		for (I=0;I<BladeCnt;I++)
		{
			for (J=0;J<bladeCutCnt[I];J++)
			{
				fputs(Line0,ocys);
				fputs(RPij[I][J].myChar,ocys);fprintf(ocys,"\n");
				fputs(RPSij[I][J].myChar,ocys);
				fputs(Line1,ocys);

				fprintf(ocys,"%6.4f",PoBij[I][J].X);
				fputs(Line11,ocys);
				fprintf(ocys,"%6.4f",PoBij[I][J].Y);
				fputs(Line12,ocys);
				fprintf(ocys,"%6.4f",PoBij[I][J].Z);
				fputs(Line13,ocys);fprintf(ocys,"\n");
				fputs(Line2,ocys);fprintf(ocys,"\n");
				fputs(Line3,ocys);
				fputs(RPij[I][J].myChar,ocys);
				fputs(Line31,ocys);fprintf(ocys,"\n");
				fputs(Line4,ocys);fprintf(ocys,"\n");
				fputs(Line5,ocys);
				fputs(RPSij[I][J].myChar,ocys);
				fputs(Line51,ocys);fprintf(ocys,"\n");
				fputs(Line6,ocys);
				fputs(setRPij[I][J].myChar,ocys);
				fputs(Line61,ocys);fprintf(ocys,"\n");
			}
		}
		fclose(ocys);
		return 0;
	} //end cord2

//***reference point end


int Pocket_Beam_Constr(char addConstraint[],myString Pij[18][30],myString setRPij[18][30],
		myString Beamij[18][30],myString CSij[18][30],int BladeCnt,int bladeCutCnt[200])
	{
		FILE *iScript;//output stream
		int I,J;
		char import1[]="from abaqus import *";
		char import2[]="from abaqusConstants import *";
		char import3[]="from caeModules import *";
		char rootAssembly[]="a = mdb.models['Model-1'].rootAssembly";
		char Line0[]="#";
		char Line1[]="region1=a.sets['";
		char Line11[]="']";
		char Line2[]="region2=a.instances['bitbody-1'].sets['";
		char Line21[]="']";//add cord id


		char Line3[]="datum = mdb.models['Model-1'].rootAssembly.instances['bitbody-1'].datums[";
		char Line31[]=".id]";
		char Line4[]="mdb.models['Model-1'].MultipointConstraint(name='";
		char Line41[]="',";
		char Line5[]="    controlPoint=region1, surface=region2, mpcType=BEAM_MPC, ";
		char Line6[]="    userMode=DOF_MODE_MPC, userType=0, csys=datum)";
		if ( (iScript=fopen(addConstraint, "w"))==NULL)//open output file
		{
			cerr << "*** ERROR: Cannot open " << addConstraint
			<< " for output." << endl;
			cin.ignore();
			cin.ignore();
			return EXIT_FAILURE;		// failure return
		} // end if
		cout<<addConstraint<<"  opened for output"<<endl;
//		cout<<endl;

		fputs(import1,iScript);
		fprintf(iScript,"\n");
		fputs(import2,iScript);
		fprintf(iScript,"\n");
		fputs(import3,iScript);
		fprintf(iScript,"\n");
		fputs(rootAssembly,iScript);
		fprintf(iScript,"\n");

		for (I=0;I<BladeCnt;I++)
		{
			for (J=0;J<bladeCutCnt[I];J++)
			{
				fputs(Line0,iScript);
				fputs(Pij[I][J].myChar,iScript);fprintf(iScript,"\n");
				fputs(Line1,iScript);
				fputs(setRPij[I][J].myChar,iScript);
				fputs(Line11,iScript);fprintf(iScript,"\n");
				fputs(Line2,iScript);fputs(Pij[I][J].myChar,iScript);
				fputs(Line21,iScript);fprintf(iScript,"\n");
				fputs(Line3,iScript);fputs(CSij[I][J].myChar,iScript);
				fputs(Line31,iScript);fprintf(iScript,"\n");
				fputs(Line4,iScript);fputs(Beamij[I][J].myChar,iScript);
				fputs(Line41,iScript);fprintf(iScript,"\n");
				fputs(Line5,iScript);fprintf(iScript,"\n");
				fputs(Line6,iScript);fprintf(iScript,"\n");
			}
		}

		fclose(iScript);

	return 0;
	} //end constraint
	//*******
int Cutter_Fcut0_LoadZ(char Fcut10Script[],myString setRPij[18][30],myString Pij[18][30],myString CSij[18][30],
		myString FCUTij[18][30],int BladeCnt,int bladeCutCnt[200])
	{
		FILE *iScript;//output stream
		int I,J;
		char import1[]="from abaqus import *";
		char import2[]="from abaqusConstants import *";
		char import3[]="from caeModules import *";
		char rootAssembly[]="a = mdb.models['Model-1'].rootAssembly";
		char Line0[]="#";
		char Line1[]="region=a.sets['";
		char Line11[]="']";
		char Line2[]="datum = mdb.models['Model-1'].rootAssembly.instances['bitbody-1'].datums[";
		char Line21[]=".id]";//add cord id
		char Line3[]="mdb.models['Model-1'].ConcentratedForce(name='";
		char Line31[]="', createStepName='Fn',";
		char Line4[]="    region=region, cf3=-10.0, distributionType=UNIFORM, field='',";
		char Line5[]="    localCsys=datum)";
		if ( (iScript=fopen(Fcut10Script, "w"))==NULL)//open output file
		{
			cerr << "*** ERROR: Cannot open " << Fcut10Script
			<< " for output." << endl;
			cin.ignore();
			cin.ignore();
			return EXIT_FAILURE;		// failure return
		} // end if
		cout<<Fcut10Script<<"  opened for output"<<endl;
//		cout<<endl;

		fputs(import1,iScript);
		fprintf(iScript,"\n");
		fputs(import2,iScript);
		fprintf(iScript,"\n");
		fputs(import3,iScript);
		fprintf(iScript,"\n");
		fputs(rootAssembly,iScript);
		fprintf(iScript,"\n");

		for (I=0;I<BladeCnt;I++)
		{
			for (J=0;J<bladeCutCnt[I];J++)
			{
				fputs(Line0,iScript);
				fputs(Pij[I][J].myChar,iScript);fprintf(iScript,"\n");
				fputs(Line1,iScript);
				fputs(setRPij[I][J].myChar,iScript);
				fputs(Line11,iScript);fprintf(iScript,"\n");
				fputs(Line2,iScript);fputs(CSij[I][J].myChar,iScript);
				fputs(Line21,iScript);fprintf(iScript,"\n");
				fputs(Line3,iScript);fputs(FCUTij[I][J].myChar,iScript);
				fputs(Line31,iScript);fprintf(iScript,"\n");
				fputs(Line4,iScript);fprintf(iScript,"\n");
				fputs(Line5,iScript);fprintf(iScript,"\n");
			}
		}

		fclose(iScript);

	return 0;
	} //end Fcut0
int Cutter_Fn0_LoadX(char Fn10Script[],myString setRPij[18][30],myString Pij[18][30],myString CSij[18][30],
		myString FNij[18][30],int BladeCnt,int bladeCutCnt[200])
	{
		FILE *iScript;//output stream
		int I,J;
		char import1[]="from abaqus import *";
		char import2[]="from abaqusConstants import *";
		char import3[]="from caeModules import *";
		char rootAssembly[]="a = mdb.models['Model-1'].rootAssembly";
		char Line0[]="#";
		char Line1[]="region=a.sets['";
		char Line11[]="']";
		char Line2[]="datum = mdb.models['Model-1'].rootAssembly.instances['bitbody-1'].datums[";
		char Line21[]=".id]";//add cord id
		char Line3[]="mdb.models['Model-1'].ConcentratedForce(name='";
		char Line31[]="', createStepName='Fn',";
		char Line4[]="    region=region, cf1=-10.0, distributionType=UNIFORM, field='',";
		char Line5[]="    localCsys=datum)";
		if ( (iScript=fopen(Fn10Script, "w"))==NULL)//open output file
		{
			cerr << "*** ERROR: Cannot open " << Fn10Script
			<< " for output." << endl;
			cin.ignore();
			cin.ignore();
			return EXIT_FAILURE;		// failure return
		} // end if
		cout<<Fn10Script<<"  opened for output"<<endl;
//		cout<<endl;

		fputs(import1,iScript);
		fprintf(iScript,"\n");
		fputs(import2,iScript);
		fprintf(iScript,"\n");
		fputs(import3,iScript);
		fprintf(iScript,"\n");
		fputs(rootAssembly,iScript);
		fprintf(iScript,"\n");

		for (I=0;I<BladeCnt;I++)
		{
			for (J=0;J<bladeCutCnt[I];J++)
			{
				fputs(Line0,iScript);
				fputs(Pij[I][J].myChar,iScript);fprintf(iScript,"\n");
				fputs(Line1,iScript);
				fputs(setRPij[I][J].myChar,iScript);
				fputs(Line11,iScript);fprintf(iScript,"\n");
				fputs(Line2,iScript);fputs(CSij[I][J].myChar,iScript);
				fputs(Line21,iScript);fprintf(iScript,"\n");
				fputs(Line3,iScript);fputs(FNij[I][J].myChar,iScript);
				fputs(Line31,iScript);fprintf(iScript,"\n");
				fputs(Line4,iScript);fprintf(iScript,"\n");
				fputs(Line5,iScript);fprintf(iScript,"\n");
			}
		}

		fclose(iScript);

	return 0;
	} //end Fn10
//Fside0
int Cutter_Fside0_LoadY(char Fside10Script[],myString setRPij[18][30],myString Pij[18][30],myString CSij[18][30],
		myString FSIDEij[18][30],int BladeCnt,int bladeCutCnt[200])
	{
		FILE *iScript;//output stream
		int I,J;
		char import1[]="from abaqus import *";
		char import2[]="from abaqusConstants import *";
		char import3[]="from caeModules import *";
		char rootAssembly[]="a = mdb.models['Model-1'].rootAssembly";
		char Line0[]="#";
		char Line1[]="region=a.sets['";
		char Line11[]="']";
		char Line2[]="datum = mdb.models['Model-1'].rootAssembly.instances['bitbody-1'].datums[";
		char Line21[]=".id]";//add cord id
		char Line3[]="mdb.models['Model-1'].ConcentratedForce(name='";
		char Line31[]="', createStepName='Fn',";
		char Line4[]="    region=region, cf2=-10.0, distributionType=UNIFORM, field='',";
		char Line5[]="    localCsys=datum)";
		if ( (iScript=fopen(Fside10Script, "w"))==NULL)//open output file
		{
			cerr << "*** ERROR: Cannot open " << Fside10Script
			<< " for output." << endl;
			cin.ignore();
			cin.ignore();
			return EXIT_FAILURE;		// failure return
		} // end if
		cout<<Fside10Script<<"  opened for output"<<endl;
//		cout<<endl;

		fputs(import1,iScript);
		fprintf(iScript,"\n");
		fputs(import2,iScript);
		fprintf(iScript,"\n");
		fputs(import3,iScript);
		fprintf(iScript,"\n");
		fputs(rootAssembly,iScript);
		fprintf(iScript,"\n");

		for (I=0;I<BladeCnt;I++)
		{
			for (J=0;J<bladeCutCnt[I];J++)
			{
				fputs(Line0,iScript);
				fputs(Pij[I][J].myChar,iScript);fprintf(iScript,"\n");
				fputs(Line1,iScript);
				fputs(setRPij[I][J].myChar,iScript);
				fputs(Line11,iScript);fprintf(iScript,"\n");
				fputs(Line2,iScript);fputs(CSij[I][J].myChar,iScript);
				fputs(Line21,iScript);fprintf(iScript,"\n");
				fputs(Line3,iScript);fputs(FSIDEij[I][J].myChar,iScript);
				fputs(Line31,iScript);fprintf(iScript,"\n");
				fputs(Line4,iScript);fprintf(iScript,"\n");
				fputs(Line5,iScript);fprintf(iScript,"\n");
			}
		}

		fclose(iScript);

	return 0;
	} //end Fside10

//
int writeCutterPTS_file(char pts_file[15],int CutNo,double radius[200],double angArnd[200],
	double height[200],double prfAng[200],double bkRake[200],double sdRake[200],double cutDia[200],
	Point3 Point0[200],Point3 Point[200])
	{
		FILE *opts;//output stream
		int I,J;
		double pi=3.141592654;
		double cosF,cosA,cosSR,cosBR,sinF,sinA,sinSR,sinBR;
		double Xij[10],Yij[10],Zij[10];
		for (I=0;I<CutNo;I++)
		{
			cosF=cos(pi/180.0*angArnd[I]);
			cosA=cos(pi/180.0*prfAng[I]);
			cosSR=cos(pi/180.0*sdRake[I]);
			cosBR=cos(pi/180.0*bkRake[I]);
			sinF=sin(pi/180.0*angArnd[I]);
			sinA=sin(pi/180.0*prfAng[I]);
			sinSR=sin(pi/180.0*sdRake[I]);
			sinBR=sin(pi/180.0*bkRake[I]);

			Xij[0]=Point0[I].X*cosF*cosA*cosSR;
			Xij[1]=Point0[I].Y*cosF*cosA*sinSR*sinBR;
			Xij[2]=Point0[I].Y*cosF*sinA*cosBR;
			Xij[3]=Point0[I].Z*cosF*cosA*sinSR*cosBR;
			Xij[4]=-Point0[I].Z*cosF*sinA*sinBR;
			Xij[5]=cosF*radius[I];
			Xij[6]=-Point0[I].X*sinF*sinSR;
			Xij[7]=Point0[I].Y*sinF*cosSR*sinBR;
			Xij[8]=Point0[I].Z*sinF*cosSR*cosBR;

			Point[I].X=0.0;
			for (J=0;J<9;J++)
			{
				Point[I].X=Point[I].X+Xij[J];
			}

			Yij[0]=Point0[I].X*sinF*cosA*cosSR;
			Yij[1]=Point0[I].Y*sinF*cosA*sinSR*sinBR;
			Yij[2]=Point0[I].Y*sinF*sinA*cosBR;
			Yij[3]=Point0[I].Z*sinF*cosA*sinSR*cosBR;
			Yij[4]=-Point0[I].Z*sinF*sinA*sinBR;
			Yij[5]=sinF*radius[I];
			Yij[6]=Point0[I].X*cosF*sinSR;
			Yij[7]=-Point0[I].Y*cosF*cosSR*sinBR;
			Yij[8]=-Point0[I].Z*cosF*cosSR*cosBR;
			Point[I].Y=0.0;
			for (J=0;J<9;J++)
			{
				Point[I].Y=Point[I].Y+Yij[J];
			}

			Zij[0]=-Point0[I].X*sinA*cosSR;
			Zij[1]=-Point0[I].Y*sinA*sinSR*sinBR;
			Zij[2]=Point0[I].Y*cosA*cosBR;
			Zij[3]=-Point0[I].Z*sinA*sinSR*cosBR;
			Zij[4]=-Point0[I].Z*cosA*sinBR;
			Zij[5]=height[I];
			Point[I].Z=0.0;
			for (J=0;J<6;J++)
			{
				Point[I].Z=Point[I].Z+Zij[J];
			}
		}
		if ( (opts=fopen(pts_file, "w"))==NULL)//open output file
		{
			cerr << "*** ERROR: Cannot open " << pts_file
			<< " for output." << endl;
			cin.ignore();
			cin.ignore();
			return EXIT_FAILURE;		// failure return
		} // end if

		cout<<pts_file<<"  opened for output"<<endl;
//		cout<<endl;

		for (I=0;I<CutNo;I++)
		{
			fprintf(opts," %7.4f %7.4f %7.4f",Point[I].X,Point[I].Y,Point[I].Z);
			fprintf(opts,"  ");
			fprintf(opts,"\n");
		}

		fclose(opts);
		return 0;
	} //end pts file
	int Set_Working_Dir(char set_working_dir[],char cae_dir[])
	{
		FILE *oScript;//output stream
		char import1[40]="from abaqus import *";
		char import2[40]="from abaqusConstants import *";
		char import3[40]="from caeModules import *";
		char Line01[]="import os";
		char Line02[]="os.chdir(r\"";
		char Line021[]="\")";
		if ( (oScript=fopen(set_working_dir, "w"))==NULL)//open output file
		{
			cerr << "*** ERROR: Cannot open " << set_working_dir
			<< " for output." << endl;
			cin.ignore();
			cin.ignore();
			return EXIT_FAILURE;		// failure return
		} // end if
		cout<<set_working_dir<<"  opened for output"<<endl;
//		cout<<endl;

		fputs(import1,oScript);fprintf(oScript,"\n");
		fputs(import2,oScript);fprintf(oScript,"\n");
		fputs(import3,oScript);fprintf(oScript,"\n");
		fputs(Line01,oScript);fprintf(oScript,"\n");
		fputs(Line02,oScript);fputs(cae_dir,oScript);
		fputs(Line021,oScript);fprintf(oScript,"\n");
		fclose(oScript);

	return 0;
	} //end set_working_dir

	int build_cae_model0(char cae_model0[],char job_name[],char cae_dir[],char cae_name[],char BitType[])
	{
		FILE *oScript;//output stream
		char import1[40]="from abaqus import *";
		char import2[40]="from abaqusConstants import *";
		char import3[40]="from caeModules import *";
		char Line00[]="Mdb()";
		char Line001[]="session.viewports['Viewport: 1'].setValues(displayedObject=None)";
		char Line01[]="mdb.models['Model-1'].Material(name='Body')";
		char Line02[]="mdb.models['Model-1'].materials['Body'].Elastic(table=((42100.0, 0.3), ))";
		char Line02s[]="mdb.models['Model-1'].materials['Body'].Elastic(table=((29700.0, 0.3), ))";
		char Line03[]="mdb.models['Model-1'].HomogeneousSolidSection(name='Body', material='Body',";
		char Line04[]="    thickness=None)";
		char Line05[]="a = mdb.models['Model-1'].rootAssembly";
		char Line06[]="mdb.models['Model-1'].StaticStep(name='Fn', previous='Initial')";
		char Line07[]="session.viewports['Viewport: 1'].assemblyDisplay.setValues(step='Fn')";
		char Line08[]="session.viewports['Viewport: 1'].assemblyDisplay.setValues(";
		char Line09[]="    adaptiveMeshConstraints=OFF)";
		char Line101[]="mdb.Job(name='";
		char Line102[]="', model='Model-1', description='', type=ANALYSIS,";
		char Line11[]="    atTime=None, waitMinutes=0, waitHours=0, queue=None, memory=90,";
		char Line12[]="    memoryUnits=PERCENTAGE, getMemoryFromAnalysis=True,";
		char Line13[]="    explicitPrecision=SINGLE, nodalOutputPrecision=SINGLE, echoPrint=OFF,";
		char Line14[]="    modelPrint=OFF, contactPrint=OFF, historyPrint=OFF, userSubroutine='',";
		char Line15[]="    scratch='', multiprocessingMode=DEFAULT, numCpus=1, numGPUs=0)";
		char Line161[]="mdb.saveAs(pathName='";
		char Line162[]="')";
		if ( (oScript=fopen(cae_model0, "w"))==NULL)//open output file
		{
			cerr << "*** ERROR: Cannot open " << cae_model0
			<< " for output." << endl;
			cin.ignore();
			cin.ignore();
			return EXIT_FAILURE;		// failure return
		} // end if
		cout<<cae_model0<<"  opened for output"<<endl;
//		cout<<endl;

		fputs(import1,oScript);fprintf(oScript,"\n");
		fputs(import2,oScript);fprintf(oScript,"\n");
		fputs(import3,oScript);fprintf(oScript,"\n");
		fputs(Line00,oScript);fprintf(oScript,"\n");
		fputs(Line001,oScript);fprintf(oScript,"\n");
		fputs(Line01,oScript);fprintf(oScript,"\n");
		if(BitType[0]=='S'||BitType[0]=='s'||BitType[strlen(BitType)-1]=='S'||BitType[strlen(BitType)-1]=='s')
		{
				fputs(Line02s,oScript);fprintf(oScript,"\n");
		}
		else
		{
				fputs(Line02,oScript);fprintf(oScript,"\n");
		}
		fputs(Line03,oScript);fprintf(oScript,"\n");
		fputs(Line04,oScript);fprintf(oScript,"\n");
		fputs(Line05,oScript);fprintf(oScript,"\n");
		fputs(Line06,oScript);fprintf(oScript,"\n");
		fputs(Line07,oScript);fprintf(oScript,"\n");
		fputs(Line08,oScript);fprintf(oScript,"\n");
		fputs(Line09,oScript);fprintf(oScript,"\n");
		fputs(Line101,oScript);fputs(job_name,oScript);
		fputs(Line102,oScript);fprintf(oScript,"\n");
		fputs(Line11,oScript);fprintf(oScript,"\n");
		fputs(Line12,oScript);fprintf(oScript,"\n");
		fputs(Line13,oScript);fprintf(oScript,"\n");
		fputs(Line14,oScript);fprintf(oScript,"\n");
		fputs(Line15,oScript);fprintf(oScript,"\n");
		fputs(Line161,oScript);fputs(cae_dir,oScript);fputs(cae_name,oScript);
		fputs(Line162,oScript);fprintf(oScript,"\n");

		fclose(oScript);
	return 0;
	} //end build cae model


	int import_part_blade_faceNew(char importStpPy[],char stpfile_dir[],char stpfile_name[],char odb_dir[],
		int BladeCntP,double bitDia,double BLadeTipCutDia[9],double BLadeTipHeight[9],double BLadeTipRadius[9],
		int bladeAngP[10],int dBladeAngP[10],double bottom1,double bottom2,double top1,double top2,double bodyDia1,double bodyDia2)
	{
		FILE *oScript;//output stream
		char import1[40]="from abaqus import *";
		char import2[40]="from abaqusConstants import *";
		char import3[40]="from caeModules import *";
		char Line011[]="step = mdb.openStep('";
		char Line012[]=".stp',";
		char Line01[]="    scaleFromFile=OFF)";
		char Line02[]="mdb.models['Model-1'].PartFromGeometryFile(name='bitbody', geometryFile=step, ";
		char Line03[]="    combine=False, dimensionality=THREE_D, type=DEFORMABLE_BODY)";
		char Line04[]="p = mdb.models['Model-1'].parts['bitbody']";
		char Line05[]="c = p.cells";
		char Line06[]="cells = c.getSequenceFromMask(mask=('[#1 ]', ), )";
		char Line07[]="p.Set(cells=cells, name='body')";
		char Line08[]="p1 = mdb.models['Model-1'].parts['bitbody']";
		char Line09[]="session.viewports['Viewport: 1'].setValues(displayedObject=p1)";
		char Line10[]="session.viewports['Viewport: 1'].view.setValues(session.views['Front'])";
		char Line11[]="session.viewports['Viewport: 1'].viewportAnnotationOptions.setValues(triad=OFF,";
		char Line12[]="    legend=OFF, title=OFF, state=OFF, annotations=OFF, compass=OFF)";
		char Line13[]="session.printOptions.setValues(reduceColors=False)";
		char Line14[]="session.printToFile(fileName='";
		char Line141[]="BODY_";
		char Line142[]="',";
		char Line15[]="    format=PNG, canvasObjects=(session.viewports['Viewport: 1'], ))";
		char Line16[]="session.viewports['Viewport: 1'].viewportAnnotationOptions.setValues(triad=ON,";
		char Line17[]="    legend=ON, title=ON, state=ON, annotations=ON, compass=ON)";
//for blade face
		double Xib[9],Yib[9],Zib[9],Xit[9],Yit[9],Zit[9],Ri[9],dummy;
		double Xob[9],Yob[9],Zob[9],Xot[9],Yot[9],Zot[9],Ro[9];
		double pi=3.141592654;
		double MultiI=0.0,MultiO=0.2;
		int bladeSlotAngI[10],bladeSlotAngO[10];
		//data for 3-points coordinates
		int I;
		myString Blade[9],BladeI[9],BladeO[9];
		strcpy(Blade[0].myChar,"blade1");
		strcpy(Blade[1].myChar,"blade2");
		strcpy(Blade[2].myChar,"blade3");
		strcpy(Blade[3].myChar,"blade4");
		strcpy(Blade[4].myChar,"blade5");
		strcpy(Blade[5].myChar,"blade6");
		strcpy(Blade[6].myChar,"blade7");
		strcpy(Blade[7].myChar,"blade8");
		strcpy(Blade[8].myChar,"blade9");
		strcpy(BladeI[0].myChar,"blade1i");
		strcpy(BladeI[1].myChar,"blade2i");
		strcpy(BladeI[2].myChar,"blade3i");
		strcpy(BladeI[3].myChar,"blade4i");
		strcpy(BladeI[4].myChar,"blade5i");
		strcpy(BladeI[5].myChar,"blade6i");
		strcpy(BladeI[6].myChar,"blade7i");
		strcpy(BladeI[7].myChar,"blade8i");
		strcpy(BladeI[8].myChar,"blade9i");
		strcpy(BladeO[0].myChar,"blade1o");
		strcpy(BladeO[1].myChar,"blade2o");
		strcpy(BladeO[2].myChar,"blade3o");
		strcpy(BladeO[3].myChar,"blade4o");
		strcpy(BladeO[4].myChar,"blade5o");
		strcpy(BladeO[5].myChar,"blade6o");
		strcpy(BladeO[6].myChar,"blade7o");
		strcpy(BladeO[7].myChar,"blade8o");
		strcpy(BladeO[8].myChar,"blade9o");
		for (I=0;I<BladeCntP;I++)
		{
			 bladeSlotAngI[I]=int(bladeAngP[I]+dBladeAngP[I]*MultiI);
			if(bladeSlotAngI[I]>360)
			{
			 bladeSlotAngI[I]=bladeSlotAngI[I]-360;
			}

			bladeSlotAngO[I]=int(bladeAngP[I]+dBladeAngP[I]*MultiO);
			if(bladeSlotAngO[I]>360)
			{
			 bladeSlotAngO[I]=bladeSlotAngO[I]-360;
			}
		}
		for(I=0;I<BladeCntP;I++)
		{
			if(BLadeTipRadius[I]>1.5)
			{
				Xib[I]=(BLadeTipRadius[I]-0.5)*cos(bladeSlotAngI[I]*pi/180.0);
				Yib[I]=(BLadeTipRadius[I]-0.5)*sin(bladeSlotAngI[I]*pi/180.0);
				Zib[I]=-0.5;
				Xit[I]=Xib[I];
				Yit[I]=Yib[I];
				Zit[I]=BLadeTipHeight[I]-BLadeTipCutDia[I]*1.5;
				Ri[I]=1.0;
			}
			else if(BLadeTipRadius[I]>1.0)
			{
			Xib[I]=(BLadeTipRadius[I]-0.25)*cos(bladeSlotAngI[I]*pi/180.0);
			Yib[I]=(BLadeTipRadius[I]-0.25)*sin(bladeSlotAngI[I]*pi/180.0);
			Zib[I]=-0.5;
			Xit[I]=Xib[I];
			Yit[I]=Yib[I];
			Zit[I]=BLadeTipHeight[I]-BLadeTipCutDia[I]*1.5;
			Ri[I]=0.75;
			}
			else if(BLadeTipRadius[I]>0.75)
			{
				Xib[I]=(BLadeTipRadius[I]-0.15)*cos(bladeSlotAngI[I]*pi/180.0);
				Yib[I]=(BLadeTipRadius[I]-0.15)*sin(bladeSlotAngI[I]*pi/180.0);
				Zib[I]=-0.5;
				Xit[I]=Xib[I];
				Yit[I]=Yib[I];
				Zit[I]=BLadeTipHeight[I]-BLadeTipCutDia[I]*0.6;
				Ri[I]=0.7;
			}
			else if(BLadeTipRadius[I]>0.5)
			{
				Xib[I]=(BLadeTipRadius[I]-0.05)*cos(bladeSlotAngI[I]*pi/180.0);
				Yib[I]=(BLadeTipRadius[I]-0.05)*sin(bladeSlotAngI[I]*pi/180.0);
				Zib[I]=-0.5;
				Xit[I]=Xib[I];
				Yit[I]=Yib[I];
				Zit[I]=BLadeTipHeight[I]-BLadeTipCutDia[I]*0.6;
				Ri[I]=0.6;
			}
			else
			{
				Xib[I]=(BLadeTipRadius[I]-0.0)*cos(bladeSlotAngI[I]*pi/180.0);
				Yib[I]=(BLadeTipRadius[I]-0.0)*sin(bladeSlotAngI[I]*pi/180.0);
				Zib[I]=-0.5;
				Xit[I]=Xib[I];
				Yit[I]=Yib[I];
				Zit[I]=BLadeTipHeight[I]-BLadeTipCutDia[I]*0.6;
				Ri[I]=0.45;
			}
			Xob[I]=(BLadeTipRadius[I]*0.0+bitDia*0.5)/2.0*cos(bladeSlotAngO[I]*pi/180.0); Xot[I]=Xob[I];
			Yob[I]=(BLadeTipRadius[I]*0.0+bitDia*0.5)/2.0*sin(bladeSlotAngO[I]*pi/180.0); Yot[I]=Yob[I];
			Zob[I]=-2.0; Zot[I]=BLadeTipHeight[I]-BLadeTipCutDia[I]*1.0;
//			Ro[I]=bitDia*0.25*dBladeAngP[I]/90.0;
			Ro[I]=(bitDia-1.0)/4.0*5.0/BladeCntP;
		}
		//normal condition

		if ( (oScript=fopen(importStpPy, "w"))==NULL)//open output file
		{
			cerr << "*** ERROR: Cannot open " << importStpPy
			<< " for output." << endl;
			cin.ignore();
			cin.ignore();
			return EXIT_FAILURE;		// failure return
		} // end if
		cout<<importStpPy<<"  opened for output"<<endl;
//		cout<<endl;
		fputs(import1,oScript);fprintf(oScript,"\n");
		fputs(import2,oScript);fprintf(oScript,"\n");
		fputs(import3,oScript);fprintf(oScript,"\n");

		fputs(Line011,oScript);fputs(stpfile_dir,oScript);fputs(stpfile_name,oScript);
		fputs(Line012,oScript);fprintf(oScript,"\n");
		fputs(Line01,oScript);fprintf(oScript,"\n");
		fputs(Line02,oScript);fprintf(oScript,"\n");
		fputs(Line03,oScript);fprintf(oScript,"\n");
		fputs(Line04,oScript);fprintf(oScript,"\n");
		fputs(Line05,oScript);fprintf(oScript,"\n");
		fputs(Line06,oScript);fprintf(oScript,"\n");
		fputs(Line07,oScript);fprintf(oScript,"\n");
		fputs(Line08,oScript);fprintf(oScript,"\n");
		fputs(Line09,oScript);fprintf(oScript,"\n");
		fputs(Line10,oScript);fprintf(oScript,"\n");
		fputs(Line11,oScript);fprintf(oScript,"\n");
		fputs(Line12,oScript);fprintf(oScript,"\n");
		fputs(Line13,oScript);fprintf(oScript,"\n");
		fputs(Line14,oScript);fputs(odb_dir,oScript);
		fputs(Line141,oScript);fputs(stpfile_name,oScript);
		fputs(Line142,oScript);fprintf(oScript,"\n");
		fputs(Line15,oScript);fprintf(oScript,"\n");
		fputs(Line16,oScript);fprintf(oScript,"\n");
		fputs(Line17,oScript);fprintf(oScript,"\n");
		//normal condition

		char BLine01[]="p = mdb.models['Model-1'].parts['bitbody']";
		char BLine02[]="s = p.faces";
//********
		char BLine0[]="#";
		char BLine1[]="side1Faces = s.getByBoundingCylinder((";
		char BLine11[]=",";
		char BLine12[]=",";
		char BLine13[]="),";
		char BLine2[]="(";
		char BLine21[]=",";
		char BLine22[]=",";
		char BLine23[]="),";
		char BLine24[]=")";
		char BLine3[]="p.Surface(side1Faces=side1Faces, name='";
		char BLine31[]="')";
		char BLineSet0[]="#Set";
		char BLineSet1[]="faces = s.getByBoundingCylinder((";
		char BLineSet11[]=",";
		char BLineSet12[]=",";
		char BLineSet13[]="),";
		char BLineSet14[]=",";
		char BLineSet15[]=",";
		char BLineSet16[]=")";
		char BLineSet2[]="(";
		char BLineSet21[]=",";
		char BLineSet22[]=",";
		char BLineSet23[]="),";
		char BLineSet24[]=")";
		char BLineSet3[]="p.Set(faces=faces, name='";
		char BLineSet31[]="')";
//for core surface
//for face_set
		char BLine007[]="#core_set";
		char BLine008[]="faces = s.getByBoundingCylinder((0.0,0.0,";
		char BLine0081[]="),";
		char BLine009[]="(0.0,0.0,";
		char BLine0091[]="),";
		char BLine0092[]=")";
		char BLine010[]="p.Set(faces=faces, name='core_face')";
		char BLine011[]="#merge_";
		char BLine012[]="p.SetByBoolean(name='";
		char BLine0121[]="', operation=DIFFERENCE, sets=(";
		char BLine013[]="    p.sets['";
		char BLine0131[]="'], p.sets['core_face'], ))";
//for faces
		char BLine027[]="#core_face";
		char BLine028[]="side1Faces1 = s.getByBoundingCylinder((0.0,0.0,";
		char BLine0281[]="),";
		char BLine029[]="(0.0,0.0,";
		char BLine0291[]="),";
		char BLine0292[]=")";
		char BLine030[]="p.Surface(side1Faces=side1Faces1, name='core_face')";
		char BLine031[]="#merge_";
		char BLine032[]="p.SurfaceByBoolean(name='";
		char BLine0321[]="', operation=DIFFERENCE, surfaces=(";
		char BLine033[]="    p.surfaces['";
		char BLine0331[]="'], p.surfaces['core_face'], ))";

		char BLine001[]="#delete face";
		char BLine0010[]="del mdb.models['Model-1'].parts['bitbody'].surfaces['";
		char BLine0011[]="']";

		char BLine002[]="#delete set";
		char BLine0020[]="del mdb.models['Model-1'].parts['bitbody'].sets['";
		char BLine0021[]="']";

		char BLine003[]="#rename faces";
		char BLine0030[]="mdb.models['Model-1'].parts['bitbody'].surfaces.changeKey(fromName='";
		char BLine0031[]="',";
		char BLine0040[]="    toName='";
		char BLine0041[]="')";

		fputs(import1,oScript);fprintf(oScript,"\n");
		fputs(import2,oScript);fprintf(oScript,"\n");
		fputs(import3,oScript);fprintf(oScript,"\n");
		fprintf(oScript,"\n");
		fputs(BLine01,oScript);fprintf(oScript,"\n");
		fputs(BLine02,oScript);fprintf(oScript,"\n");
		fprintf(oScript,"\n");
		for (I=0;I<BladeCntP;I++)//surfaces
		{
				fputs(BLine0,oScript);
				fputs(BladeI[I].myChar,oScript);fprintf(oScript,"\n");

				fputs(BLine1,oScript);
				fprintf(oScript,"%5.2f",Xib[I]);fputs(BLine11,oScript);
				fprintf(oScript,"%5.2f",Yib[I]);fputs(BLine12,oScript);
				fprintf(oScript,"%5.2f",Zib[I]);fputs(BLine13,oScript);
				fprintf(oScript,"\n");
				fputs(BLine2,oScript);
				fprintf(oScript,"%5.2f",Xit[I]);fputs(BLine21,oScript);
				fprintf(oScript,"%5.2f",Yit[I]);fputs(BLine22,oScript);
				fprintf(oScript,"%5.2f",Zit[I]);fputs(BLine23,oScript);
				fprintf(oScript,"%5.2f",Ri[I]);fputs(BLine24,oScript);
				fprintf(oScript,"\n");
				fputs(BLine3,oScript);
				fputs(BladeI[I].myChar,oScript);
				fputs(BLine31,oScript);fprintf(oScript,"\n");
				fputs(BLine0,oScript);
				fputs(BladeO[I].myChar,oScript);fprintf(oScript,"\n");
				fputs(BLine1,oScript);
				fprintf(oScript,"%5.2f",Xob[I]);fputs(BLine11,oScript);
				fprintf(oScript,"%5.2f",Yob[I]);fputs(BLine12,oScript);
				fprintf(oScript,"%5.2f",Zob[I]);fputs(BLine13,oScript);
				fprintf(oScript,"\n");
				fputs(BLine2,oScript);
				fprintf(oScript,"%5.2f",Xot[I]);fputs(BLine21,oScript);
				fprintf(oScript,"%5.2f",Yot[I]);fputs(BLine22,oScript);
				fprintf(oScript,"%5.2f",Zot[I]);fputs(BLine23,oScript);
				fprintf(oScript,"%5.2f",Ro[I]);fputs(BLine24,oScript);
				fprintf(oScript,"\n");
				fputs(BLine3,oScript);
				fputs(BladeO[I].myChar,oScript);
				fputs(BLine31,oScript);fprintf(oScript,"\n");
		}
				fputs(BLine0,oScript);fprintf(oScript,"\n");
//core face
				fputs(BLine027,oScript);fprintf(oScript,"\n");
				fputs(BLine028,oScript);
				fprintf(oScript,"%4.2f",bottom2);
				fputs(BLine0281,oScript);fprintf(oScript,"\n");
				fputs(BLine029,oScript);
				fprintf(oScript,"%4.2f",top1);
				fputs(BLine0291,oScript);
				fprintf(oScript,"%4.2f",bodyDia2/2.0);
				fputs(BLine0292,oScript);fprintf(oScript,"\n");
				fputs(BLine030,oScript);fprintf(oScript,"\n");
			for (I=0;I<BladeCntP;I++)//surfaces
			{
					fputs(BLine031,oScript);fputs(Blade[I].myChar,oScript);fprintf(oScript,"\n");
					fputs(BLine032,oScript);
					fputs(Blade[I].myChar,oScript);
					fputs(BLine0321,oScript);fprintf(oScript,"\n");
					fputs(BLine033,oScript);
					fputs(BladeO[I].myChar,oScript);
					fputs(BLine0331,oScript);fprintf(oScript,"\n");
			}

			for (I=0;I<BladeCntP;I++)//face set
			{
				fputs(BLineSet0,oScript);
				fputs(BladeI[I].myChar,oScript);fprintf(oScript,"\n");

				fputs(BLineSet1,oScript);
				fprintf(oScript,"%5.2f",Xib[I]);fputs(BLineSet11,oScript);
				fprintf(oScript,"%5.2f",Yib[I]);fputs(BLineSet12,oScript);
				fprintf(oScript,"%5.2f",Zib[I]);fputs(BLineSet13,oScript);
				fprintf(oScript,"\n");
				fputs(BLineSet2,oScript);
				fprintf(oScript,"%5.2f",Xit[I]);fputs(BLineSet21,oScript);
				fprintf(oScript,"%5.2f",Yit[I]);fputs(BLineSet22,oScript);
				fprintf(oScript,"%5.2f",Zit[I]);fputs(BLineSet23,oScript);
				fprintf(oScript,"%5.2f",Ri[I]);fputs(BLineSet24,oScript);
				fprintf(oScript,"\n");
				fputs(BLineSet3,oScript);
				fputs(BladeI[I].myChar,oScript);
				fputs(BLineSet31,oScript);fprintf(oScript,"\n");
				fputs(BLineSet0,oScript);
				fputs(BladeO[I].myChar,oScript);fprintf(oScript,"\n");
				fputs(BLineSet1,oScript);
				fprintf(oScript,"%5.2f",Xob[I]);fputs(BLineSet11,oScript);
				fprintf(oScript,"%5.2f",Yob[I]);fputs(BLineSet12,oScript);
				fprintf(oScript,"%5.2f",Zob[I]);fputs(BLineSet13,oScript);
				fprintf(oScript,"\n");
				fputs(BLineSet2,oScript);
				fprintf(oScript,"%5.2f",Xot[I]);fputs(BLineSet21,oScript);
				fprintf(oScript,"%5.2f",Yot[I]);fputs(BLineSet22,oScript);
				fprintf(oScript,"%5.2f",Zot[I]);fputs(BLineSet23,oScript);
				fprintf(oScript,"%5.2f",Ro[I]);fputs(BLineSet24,oScript);
				fprintf(oScript,"\n");
				fputs(BLineSet3,oScript);
				fputs(BladeO[I].myChar,oScript);
				fputs(BLineSet31,oScript);fprintf(oScript,"\n");
			}
//core set
				fputs(BLine007,oScript);fprintf(oScript,"\n");
				fputs(BLine008,oScript);
				fprintf(oScript,"%4.2f",bottom2);
				fputs(BLine0081,oScript);fprintf(oScript,"\n");
				fputs(BLine009,oScript);
				fprintf(oScript,"%4.2f",top1);
				fputs(BLine0091,oScript);
				fprintf(oScript,"%4.2f",bodyDia2/2.0);
				fputs(BLine0092,oScript);fprintf(oScript,"\n");
				fputs(BLine010,oScript);fprintf(oScript,"\n");
				for (I=0;I<BladeCntP;I++)//surfaces
				{
					fputs(BLine011,oScript);fputs(Blade[I].myChar,oScript);fprintf(oScript,"\n");
					fputs(BLine012,oScript);
					fputs(Blade[I].myChar,oScript);
					fputs(BLine0121,oScript);fprintf(oScript,"\n");
					fputs(BLine013,oScript);
					fputs(BladeO[I].myChar,oScript);
					fputs(BLine0131,oScript);fprintf(oScript,"\n");
				}
//delete BladeI face
/*				fputs(BLine001,oScript);fprintf(oScript,"\n");
				for (I=0;I<BladeCntP;I++)//surfaces
				{
					fputs(BLine0010,oScript);
					fputs(BladeI[I].myChar,oScript);
					fputs(BLine0011,oScript);fprintf(oScript,"\n");
				}*/
//delete BladeO face
				fputs(BLine001,oScript);fprintf(oScript,"\n");
				for (I=0;I<BladeCntP;I++)//surfaces
				{
					fputs(BLine0010,oScript);
					fputs(BladeO[I].myChar,oScript);
					fputs(BLine0011,oScript);fprintf(oScript,"\n");
				}
//rename face Blade to BladeO
				fputs(BLine003,oScript);fprintf(oScript,"\n");
				for (I=0;I<BladeCntP;I++)//surfaces
				{
					fputs(BLine0030,oScript);
					fputs(Blade[I].myChar,oScript);
					fputs(BLine0031,oScript);fprintf(oScript,"\n");
					fputs(BLine0040,oScript);
					fputs(BladeO[I].myChar,oScript);
					fputs(BLine0041,oScript);fprintf(oScript,"\n");
				}
//delete BladeI faceset
				fputs(BLine002,oScript);fprintf(oScript,"\n");
				for (I=0;I<BladeCntP;I++)//surfaces
				{
					fputs(BLine0020,oScript);
					fputs(BladeI[I].myChar,oScript);
					fputs(BLine0021,oScript);fprintf(oScript,"\n");
				}
//delete BladeO faceset
				fputs(BLine002,oScript);fprintf(oScript,"\n");
				for (I=0;I<BladeCntP;I++)//surfaces
				{
					fputs(BLine0020,oScript);
					fputs(BladeO[I].myChar,oScript);
					fputs(BLine0021,oScript);fprintf(oScript,"\n");
				}


		fclose(oScript);
	return 0;
	}//end import part add bldface
int sect_assign(char sectAssignPy[])
	{
		FILE *oScript;//output stream
		char import1[40]="from abaqus import *";
		char import2[40]="from abaqusConstants import *";
		char import3[40]="from caeModules import *";
		char Line01[]="p = mdb.models['Model-1'].parts['bitbody']";
//		char Line02[]="c = p.cells";
//		char Line03[]="cells = c.getSequenceFromMask(mask=('[#1 ]', ), )";
//		char Line04[]="region = p.Set(cells=cells, name='Set-1')";
		char Line04[]="region = p.sets['body']";
		char Line05[]="p = mdb.models['Model-1'].parts['bitbody']";
		char Line06[]="p.SectionAssignment(region=region, sectionName='Body', offset=0.0,";
		char Line07[]="    offsetType=MIDDLE_SURFACE, offsetField='',";
		char Line08[]="    thicknessAssignment=FROM_SECTION)";


		if ( (oScript=fopen(sectAssignPy, "w"))==NULL)//open output file
		{
			cerr << "*** ERROR: Cannot open " << sectAssignPy
			<< " for output." << endl;
			cin.ignore();
			cin.ignore();
			return EXIT_FAILURE;		// failure return
		} // end if
		cout<<sectAssignPy<<"  opened for output"<<endl;
//		cout<<endl;

		fputs(import1,oScript);fprintf(oScript,"\n");
		fputs(import2,oScript);fprintf(oScript,"\n");
		fputs(import3,oScript);fprintf(oScript,"\n");

		fputs(Line01,oScript);fprintf(oScript,"\n");
//		fputs(Line02,oScript);fprintf(oScript,"\n");
//		fputs(Line03,oScript);fprintf(oScript,"\n");
		fputs(Line04,oScript);fprintf(oScript,"\n");
		fputs(Line05,oScript);fprintf(oScript,"\n");
		fputs(Line06,oScript);fprintf(oScript,"\n");
		fputs(Line07,oScript);fprintf(oScript,"\n");
		fputs(Line08,oScript);fprintf(oScript,"\n");
		fclose(oScript);

	return 0;
	}

int add_instance(char instancePy[])
	{
		FILE *oScript;//output stream
		char import1[40]="from abaqus import *";
		char import2[40]="from abaqusConstants import *";
		char import3[40]="from caeModules import *";
		char Line01[]="a = mdb.models['Model-1'].rootAssembly";
		char Line02[]="p = mdb.models['Model-1'].parts['bitbody']";
		char Line03[]="a.Instance(name='bitbody-1', part=p, dependent=ON)";
		char Line04[]="session.viewports['Viewport: 1'].setValues(displayedObject=p)";

		if ( (oScript=fopen(instancePy, "w"))==NULL)//open output file
		{
			cerr << "*** ERROR: Cannot open " << instancePy
			<< " for output." << endl;
			cin.ignore();
			cin.ignore();
			return EXIT_FAILURE;		// failure return
		} // end if
		cout<<instancePy<<"  opened for output"<<endl;
//		cout<<endl;

		fputs(import1,oScript);fprintf(oScript,"\n");
		fputs(import2,oScript);fprintf(oScript,"\n");
		fputs(import3,oScript);fprintf(oScript,"\n");

		fputs(Line01,oScript);fprintf(oScript,"\n");
		fputs(Line02,oScript);fprintf(oScript,"\n");
		fputs(Line03,oScript);fprintf(oScript,"\n");
		fputs(Line04,oScript);fprintf(oScript,"\n");
		fclose(oScript);

	return 0;
	}

int mesh_part(char meshPartPy[],double bitDia)
	{
		FILE *oScript;//output stream
		char import1[40]="from abaqus import *";
		char import2[40]="from abaqusConstants import *";
		char import3[40]="from caeModules import *";
		char Line01[]="p = mdb.models['Model-1'].parts['bitbody']";
		char Line02[]="c = p.cells";
		char Line03[]="pickedRegions = c.getSequenceFromMask(mask=('[#1 ]', ), )";
		char Line04[]="p.setMeshControls(regions=pickedRegions, elemShape=TET, technique=FREE,";
		char Line05[]="    allowMapped=False, sizeGrowthRate=1.25)";
		char Line06[]="elemType1 = mesh.ElemType(elemCode=C3D20R)";
		char Line07[]="elemType2 = mesh.ElemType(elemCode=C3D15)";
		char Line08[]="elemType3 = mesh.ElemType(elemCode=C3D10)";
		char Line09[]="cells = c.getSequenceFromMask(mask=('[#1 ]', ), )";
		char Line10[]="pickedRegions =(cells, )";
		char Line11[]="p.setElementType(regions=pickedRegions, elemTypes=(elemType1, elemType2,";
		char Line12[]="    elemType3))";
		char Line13[]="p.seedPart(size=";
		char Line131[]=", deviationFactor=0.1, minSizeFactor=0.1)";
		char Line14[]="p.createVirtualTopology(mergeShortEdges=True, shortEdgeThreshold=0.046,";
		char Line15[]="    mergeSmallFaces=True, smallFaceAreaThreshold=0.011, mergeSliverFaces=True,";
		char Line16[]="    faceAspectRatioThreshold=10.0, mergeSmallAngleFaces=True,";
		char Line17[]="    smallFaceCornerAngleThreshold=10.0, mergeThinStairFaces=True,";
		char Line18[]="    thinStairFaceThreshold=0.0092, ignoreRedundantEntities=True,";
		char Line19[]="    cornerAngleTolerance=30.0, applyBlendControls=True,";
		char Line20[]="    blendSubtendedAngleTolerance=60.0, blendRadiusTolerance=0.23)";
		char Line21[]="p.generateMesh()";
		double mesh_size=0.12;
		if (bitDia>=12.0)
		{
			mesh_size=0.12;
		}
		else if (bitDia>=11.0)
		{
			mesh_size=0.12;
		}
		else if (bitDia>=10.0)
		{
			mesh_size=0.11;
		}
		else if (bitDia>=9.0)
		{
			mesh_size=0.10;
		}
		else if (bitDia>=8.0)
		{
			mesh_size=0.09;
		}
		else if (bitDia>=7.0)
		{
			mesh_size=0.08;
		}
		else if (bitDia>=6.0)
		{
			mesh_size=0.07;
		}
		else if (bitDia>=5.0)
		{
			mesh_size=0.06;
		}
		else if (bitDia>=4.0)
		{
			mesh_size=0.05;
		}
		else
		{
			mesh_size=0.04;
		}

		if ( (oScript=fopen(meshPartPy, "w"))==NULL)//open output file
		{
			cerr << "*** ERROR: Cannot open " << meshPartPy
			<< " for output." << endl;
			cin.ignore();
			cin.ignore();
			return EXIT_FAILURE;		// failure return
		} // end if
		cout<<meshPartPy<<"  opened for output"<<endl;
//		cout<<endl;

		fputs(import1,oScript);fprintf(oScript,"\n");
		fputs(import2,oScript);fprintf(oScript,"\n");
		fputs(import3,oScript);fprintf(oScript,"\n");

		fputs(Line01,oScript);fprintf(oScript,"\n");
		fputs(Line02,oScript);fprintf(oScript,"\n");
		fputs(Line03,oScript);fprintf(oScript,"\n");
		fputs(Line04,oScript);fprintf(oScript,"\n");
		fputs(Line05,oScript);fprintf(oScript,"\n");
		fputs(Line06,oScript);fprintf(oScript,"\n");
		fputs(Line07,oScript);fprintf(oScript,"\n");
		fputs(Line08,oScript);fprintf(oScript,"\n");
		fputs(Line09,oScript);fprintf(oScript,"\n");
		fputs(Line10,oScript);fprintf(oScript,"\n");
		fputs(Line11,oScript);fprintf(oScript,"\n");
		fputs(Line12,oScript);fprintf(oScript,"\n");
		fputs(Line13,oScript);
		fprintf(oScript,"%4.2f",mesh_size);
		fputs(Line131,oScript);fprintf(oScript,"\n");
		fputs(Line14,oScript);fprintf(oScript,"\n");
		fputs(Line15,oScript);fprintf(oScript,"\n");
		fputs(Line16,oScript);fprintf(oScript,"\n");
		fputs(Line17,oScript);fprintf(oScript,"\n");
		fputs(Line18,oScript);fprintf(oScript,"\n");
		fputs(Line19,oScript);fprintf(oScript,"\n");
		fputs(Line20,oScript);fprintf(oScript,"\n");
		fputs(Line21,oScript);fprintf(oScript,"\n");
		fclose(oScript);

	return 0;
	} //end mesh_part

int bc_fixed(char bcFixedPy[])
	{
		FILE *oScript;//output stream
		char import1[40]="from abaqus import *";
		char import2[40]="from abaqusConstants import *";
		char import3[40]="from caeModules import *";
		char Line01[]="a = mdb.models['Model-1'].rootAssembly";
		char Line02[]="region = a.instances['bitbody-1'].sets['shoulder']";
		char Line03[]="mdb.models['Model-1'].DisplacementBC(name='Fixed', createStepName='Fn',";
		char Line04[]="    region=region, u1=0.0, u2=0.0, u3=0.0, ur1=0.0, ur2=0.0, ur3=0.0,";
		char Line05[]="    amplitude=UNSET, fixed=OFF, distributionType=UNIFORM, fieldName='',";
		char Line06[]="    localCsys=None)";
		if ( (oScript=fopen(bcFixedPy, "w"))==NULL)//open output file
		{
			cerr << "*** ERROR: Cannot open " << bcFixedPy
			<< " for output." << endl;
			cin.ignore();
			cin.ignore();
			return EXIT_FAILURE;		// failure return
		} // end if
		cout<<bcFixedPy<<"  opened for output"<<endl;
//		cout<<endl;

		fputs(import1,oScript);fprintf(oScript,"\n");
		fputs(import2,oScript);fprintf(oScript,"\n");
		fputs(import3,oScript);fprintf(oScript,"\n");

		fputs(Line01,oScript);fprintf(oScript,"\n");
		fputs(Line02,oScript);fprintf(oScript,"\n");
		fputs(Line03,oScript);fprintf(oScript,"\n");
		fputs(Line04,oScript);fprintf(oScript,"\n");
		fputs(Line05,oScript);fprintf(oScript,"\n");
		fputs(Line06,oScript);fprintf(oScript,"\n");
		fclose(oScript);

	return 0;
	}

int Print_Stresses(char PrintStressPY[],char odb_dir[],char job_name[],
				   double uplimit,double lowlimit,char BitType[])
	{
		char extPy[]=".py";//stress file extension
		//char MisesPy[]="Mises.py";//stress file extension
		strcpy (PrintStressPY+strlen(PrintStressPY),extPy);
		/*char PrincipalStress[] = "STRESS";
		strcpy (PrincipalStress+strlen(PrincipalStress),MaxPPy);
		if(BitType[0]=='S'||BitType[0]=='s'||BitType[strlen(BitType)-1]=='S'||BitType[strlen(BitType)-1]=='s')
		{
			strcpy (PrintStressPY+strlen(PrintStressPY),MisesPy);
		}
		else
		{
			strcpy (PrintStressPY+strlen(PrintStressPY),MaxPPy);
		}*/
		FILE *oScript;//output stream
		char import1[40]="from abaqus import *";
		char import2[40]="from abaqusConstants import *";
		char import3[40]="from caeModules import *";
		char import4[40]="from odbAccess import *";

//		char Line001[]="leaf = dgo.Leaf(leafType=DEFAULT_MODEL)";
        char Line00001[] = "session.viewports['Viewport: 1'].partDisplay.setValues(mesh=OFF)";
        char Line0001[] = "p = mdb.models['Model-1'].parts['bitbody']";
        char Line0002[] = "session.viewports['Viewport: 1'].setValues(displayedObject=p)";
        char Line0003[] = "session.viewports['Viewport: 1'].partDisplay.geometryOptions.setValues(";
        char Line0004[] = "    datumAxes=ON, datumCoordSystems=OFF)";
        char Line0005[] = "session.viewports['Viewport: 1'].view.setValues(session.views['Front'])";
        char Line0006[] = "session.printToFile(fileName='BitBodyFaceView', format=PNG, canvasObjects=(";
        char Line0007[] = "    session.viewports['Viewport: 1'], ))";
        char Line0008[] = "session.viewports['Viewport: 1'].view.setValues(session.views['Bottom'])";
        char Line0009[] = "session.printToFile(fileName='BitBodyRightView', format=PNG, canvasObjects=(";
        char Line0010[] = "    session.viewports['Viewport: 1'], ))";
        char Line0010i[] = "session.viewports['Viewport: 1'].view.setValues(session.views['Front'])";
        char Line0010i1[] = "session.viewports['Viewport: 1'].partDisplay.setValues(mesh=ON)";
        char Line0010i2[] = "session.printToFile(fileName='MESH_";
        char Line0010i3[] = "',format=PNG, canvasObjects=(";
        char Line0010i4[] = "session.viewports['Viewport: 1'], ))";

        char Line0011[] = "odb = openOdb('";

        char Line0012[] = ".odb')";
        char Line0013[] = "session.viewports['Viewport: 1'].setValues(displayedObject=odb)";

		char Line001[]="leaf = dgo.LeafFromElementSets(elementSets=('BITBODY-1.BODY', ))";
		char Line002[]="session.viewports['Viewport: 1'].odbDisplay.displayGroup.replace(leaf=leaf)";
		char Line01[]="session.viewports['Viewport: 1'].view.setValues(session.views['Front'])";
		char Line02[]="session.viewports['Viewport: 1'].viewportAnnotationOptions.setValues(triad=OFF,";
		char Line03[]="    title=OFF, state=OFF, annotations=OFF, compass=OFF, legend=ON)";
		char Line08[]="session.viewports['Viewport: 1'].odbDisplay.commonOptions.setValues(";
		char Line09[]="    visibleEdges=FREE, deformationScaling=UNIFORM, uniformScaleFactor=1)";
		char Line10[]="session.viewports['Viewport: 1'].odbDisplay.setPrimaryVariable(";
		char Line11[]="    variableLabel='S', outputPosition=INTEGRATION_POINT, refinement=(INVARIANT,";
		char Line12[]="    'Max. Principal'), )";
		char Line12s[]="    'Mises'), )";
		char Line13[]="session.viewports['Viewport: 1'].odbDisplay.display.setValues(";
		char Line14[]="    plotState=CONTOURS_ON_DEF)";
		char Line17[]="session.viewports['Viewport: 1'].odbDisplay.contourOptions.setValues(";
		char Line181[]="    maxAutoCompute=OFF, maxValue=";
		char Line182[]=", minAutoCompute=OFF, minValue=";
		char Line183[]=",";
		char Line184[]="    showMaxLocation=OFF)";

		char Line19[]="session.printOptions.setValues(reduceColors=False)";
		char Line211[]="session.printToFile(fileName='";
		char Line212[]="MaxP";
		char Line212s[]="Mises";
		char Line213[]="',";
		char Line22[]="     format=PNG,canvasObjects=(session.viewports['Viewport: 1'], ))";
		if ( (oScript=fopen(PrintStressPY, "w"))==NULL)//open output file
		{
			cerr << "*** ERROR: Cannot open " << PrintStressPY
			<< " for output." << endl;
			cin.ignore();
			cin.ignore();
			return EXIT_FAILURE;		// failure return
		} // end if
		cout<<PrintStressPY<<"  opened for output"<<endl;
//		cout<<endl;
		fputs(import1,oScript);fprintf(oScript,"\n");
		fputs(import2,oScript);fprintf(oScript,"\n");
		fputs(import3,oScript);fprintf(oScript,"\n");
		fputs(import4,oScript);fprintf(oScript,"\n");

        fputs(Line00001,oScript);fprintf(oScript,"\n");
		fputs(Line0001,oScript);fprintf(oScript,"\n");
		fputs(Line0002,oScript);fprintf(oScript,"\n");

		fputs(Line0003,oScript);fprintf(oScript,"\n");
		fputs(Line0004,oScript);fprintf(oScript,"\n");
		fputs(Line0005,oScript);fprintf(oScript,"\n");
		fputs(Line0006,oScript);fprintf(oScript,"\n");
		fputs(Line0007,oScript);fprintf(oScript,"\n");
		fputs(Line0008,oScript);fprintf(oScript,"\n");
		fputs(Line0009,oScript);fprintf(oScript,"\n");
		fputs(Line0010,oScript);fprintf(oScript,"\n");
		fputs(Line0010i,oScript);fprintf(oScript,"\n");
		fputs(Line0010i1,oScript);fprintf(oScript,"\n");
		fputs(Line0010i2,oScript);fputs(job_name,oScript);
		fputs(Line0010i3,oScript);fprintf(oScript,"\n");
		fputs(Line0010i4,oScript);fprintf(oScript,"\n");
		fputs(Line0011,oScript);fputs(odb_dir,oScript);
		fputs(job_name,oScript);
		fputs(Line0012,oScript);fprintf(oScript,"\n");
		fputs(Line0013,oScript);fprintf(oScript,"\n");


		fputs(Line001,oScript);fprintf(oScript,"\n");
		fputs(Line002,oScript);fprintf(oScript,"\n");
		fputs(Line01,oScript);fprintf(oScript,"\n");
		fputs(Line02,oScript);fprintf(oScript,"\n");
		fputs(Line03,oScript);fprintf(oScript,"\n");
		fputs(Line08,oScript);fprintf(oScript,"\n");
		fputs(Line09,oScript);fprintf(oScript,"\n");

		//Max Principal stress plot
		fputs(Line10,oScript);fprintf(oScript,"\n");
		fputs(Line11,oScript);fprintf(oScript,"\n");
		fputs(Line12,oScript);
		fprintf(oScript,"\n");

		fputs(Line13,oScript);fprintf(oScript,"\n");
		fputs(Line14,oScript);fprintf(oScript,"\n");
		fputs(Line17,oScript);fprintf(oScript,"\n");
		fputs(Line181,oScript);fprintf(oScript,"%5.2f",uplimit);
		fputs(Line182,oScript);fprintf(oScript,"%5.2f",lowlimit);
		fputs(Line183,oScript);fprintf(oScript,"\n");
		fputs(Line184,oScript);fprintf(oScript,"\n");

		fputs(Line19,oScript);fprintf(oScript,"\n");
		fputs(Line211,oScript);fputs(odb_dir,oScript);
		fputs(Line212,oScript);
		fputs(job_name,oScript);
		fputs(Line213,oScript);fprintf(oScript,"\n");
		fputs(Line22,oScript);fprintf(oScript,"\n");

		//von Mises stress plot
		fputs(Line10,oScript);fprintf(oScript,"\n");
		fputs(Line11,oScript);fprintf(oScript,"\n");
		fputs(Line12s,oScript);
		fprintf(oScript,"\n");
		fputs(Line19,oScript);fprintf(oScript,"\n");
		fputs(Line211,oScript);fputs(odb_dir,oScript);
		fputs(Line212s,oScript);
		fputs(job_name,oScript);
		fputs(Line213,oScript);fprintf(oScript,"\n");
		fputs(Line22,oScript);fprintf(oScript,"\n");



		fclose(oScript);

	return 0;
	}
int PrintBodyFaceSet_Stresses(char PrintBodyFaceSetStressPY[],char odb_dir[],char job_name[],char BitType[],int BladeCntP,double uplimit,double lowlimit)
	{
		//char MaxPPy[]="MaxP.py";//stress file extension
		//char MisesPy[]="Mises.py";//stress file extension
		char extPy[]=".py";
		strcpy (PrintBodyFaceSetStressPY+strlen(PrintBodyFaceSetStressPY),extPy);
		/*
		if(BitType[0]=='S'||BitType[0]=='s'||BitType[strlen(BitType)-1]=='S'||BitType[strlen(BitType)-1]=='s')
		{
			strcpy (PrintBodyFaceSetStressPY+strlen(PrintBodyFaceSetStressPY),MisesPy);
		}
		else
		{
			strcpy (PrintBodyFaceSetStressPY+strlen(PrintBodyFaceSetStressPY),MaxPPy);
		}*/
		int I;
		myString BodyFaceSet;
		strcpy(BodyFaceSet.myChar,"BODY_FACE");

		myString StressBodyFaceSet;
		char PrintStess[30],odb[]=".odb";
		/*
		if(BitType[0]=='S'||BitType[0]=='s'||BitType[strlen(BitType)-1]=='S'||BitType[strlen(BitType)-1]=='s')
		{
		strcpy(StressBodyFaceSet.myChar,"Mises_BodyFaceSet");
		strcpy(PrintStess,"    'Mises'), )");
		}
		else
		{
		strcpy(StressBodyFaceSet.myChar,"MaxP_BodyFaceSet");
		strcpy(PrintStess,"    'Max. Principal'), )");
		}
		*/
		FILE *oScript;//output stream
		char import1[40]="from abaqus import *";
		char import2[40]="from abaqusConstants import *";
		char import3[40]="from caeModules import *";
		char Line01[]="o1 = session.openOdb(";
		char Line02[]="    name='";
		char Line021[]="')";
		char Line03[]="session.viewports['Viewport: 1'].setValues(displayedObject=o1)";
		char Line04[]="session.viewports['Viewport: 1'].odbDisplay.commonOptions.setValues(";
		char Line05[]="    visibleEdges=NONE, deformationScaling=UNIFORM, uniformScaleFactor=1)";
		char Line06[]="session.viewports['Viewport: 1'].viewportAnnotationOptions.setValues(triad=ON,";
		char Line07[]="    legend=ON, title=OFF, state=OFF, annotations=OFF, compass=OFF)";
		char Line08[]="session.viewports['Viewport: 1'].odbDisplay.contourOptions.setValues(";
		char Line09[]="    maxAutoCompute=ON, minAutoCompute=ON, showMaxLocation=ON)";
		char Line10[]="session.viewports['Viewport: 1'].odbDisplay.setPrimaryVariable(";
		char Line11[]="    variableLabel='S', outputPosition=INTEGRATION_POINT, refinement=(INVARIANT,";
		char Line11a[] = "    'Max. Principal'), )";
		char Line11b[] = "    'Mises'), )";
		char Line12[]="session.viewports['Viewport: 1'].odbDisplay.display.setValues(";
		char Line13[]="    plotState=CONTOURS_ON_DEF)";
		char Line14[]="session.printOptions.setValues(reduceColors=False)";
		char Line15[]="session.viewports['Viewport: 1'].view.setValues(session.views['Front'])";
		char Line20[]="#";
		char Line21[]="leaf = dgo.LeafFromElementSets(elementSets=('BITBODY-1.";
		char Line211[]="', ))";
		char Line22[]="session.viewports['Viewport: 1'].odbDisplay.displayGroup.replace(leaf=leaf)";

		char Line28[]="session.viewports['Viewport: 1'].odbDisplay.contourOptions.setValues(";
		char Line29[]="    maxAutoCompute=OFF, maxValue=";
		char Line30[]=", minAutoCompute=OFF, minValue=";
		char Line31[]=",";
		char Line32[]="    showMaxLocation=ON)";

		char Line23[]="session.printToFile(fileName='";

		char Line23a[] = "MaxP_BodyFaceSet";
		char Line23b[] = "Mises_BodyFaceSet";
		char Line231[]="',";
		char Line24[]="     format=PNG,canvasObjects=(session.viewports['Viewport: 1'], ))";

        char Line25[]="session.fieldReportOptions.setValues(printXYData=OFF, printTotal=OFF)";
        char Line26[]="session.writeFieldReport(fileName='";
        char Line26a[] = "maxstressMaxP.rpt";
        char Line26b[] = "maxstressMises.rpt";
        char Line26i[] = "', append=OFF, sortItem='Node Label', odb=odb, step=0, frame=1, outputPosition=NODAL,";
        char Line27[]  = "variable=(('S', INTEGRATION_POINT, ((INVARIANT, 'Max. Principal'), )), ))";
        char Line27i[] = "variable=(('S', INTEGRATION_POINT, ((INVARIANT, 'Mises'), )), ))";

		if ( (oScript=fopen(PrintBodyFaceSetStressPY, "w"))==NULL)//open output file
		{
			cerr << "*** ERROR: Cannot open " << PrintBodyFaceSetStressPY
			<< " for output." << endl;
			cin.ignore();
			cin.ignore();
			return EXIT_FAILURE;		// failure return
		} // end if
		cout<<PrintBodyFaceSetStressPY<<"  opened for output"<<endl;
		cout<<endl;
		fputs(import1,oScript);fprintf(oScript,"\n");
		fputs(import2,oScript);fprintf(oScript,"\n");
		fputs(import3,oScript);fprintf(oScript,"\n");
		fputs(Line04,oScript);fprintf(oScript,"\n");
		fputs(Line05,oScript);fprintf(oScript,"\n");
		fputs(Line06,oScript);fprintf(oScript,"\n");
		fputs(Line07,oScript);fprintf(oScript,"\n");
		fputs(Line08,oScript);fprintf(oScript,"\n");
		fputs(Line09,oScript);fprintf(oScript,"\n");

    //Print PNG files for Max Principal stress
		fputs(Line10,oScript);fprintf(oScript,"\n");
		fputs(Line11,oScript);fprintf(oScript,"\n");
		fputs(Line11a,oScript);fprintf(oScript,"\n");
		fputs(Line12,oScript);fprintf(oScript,"\n");
		fputs(Line13,oScript);fprintf(oScript,"\n");
		fputs(Line14,oScript);fprintf(oScript,"\n");
		fputs(Line15,oScript);fprintf(oScript,"\n");

		fputs(Line20,oScript);
		fputs(BodyFaceSet.myChar,oScript);fprintf(oScript,"\n");
		fputs(Line21,oScript);
		fputs(BodyFaceSet.myChar,oScript);
		fputs(Line211,oScript);fprintf(oScript,"\n");
		fputs(Line22,oScript);fprintf(oScript,"\n");

		fputs(Line28,oScript);fprintf(oScript,"\n");
		fputs(Line29,oScript);fprintf(oScript,"%5.2f",uplimit);
		fputs(Line30,oScript);fprintf(oScript,"%5.2f",lowlimit);
		fputs(Line31,oScript);fprintf(oScript,"\n");
		fputs(Line32,oScript);fprintf(oScript,"\n");

		fputs(Line23,oScript);
		fputs(Line23a,oScript);
		fputs(Line231,oScript);fprintf(oScript,"\n");
		fputs(Line24,oScript);fprintf(oScript,"\n");

		fputs(Line25,oScript);fprintf(oScript,"\n");
		fputs(Line26,oScript);
		fputs(Line26a,oScript);
		fputs(Line26i,oScript);
		fputs(Line27,oScript);fprintf(oScript,"\n");

    //Print PNG files for von-Mises stress
		fputs(Line10,oScript);fprintf(oScript,"\n");
		fputs(Line11,oScript);fprintf(oScript,"\n");
		fputs(Line11b,oScript);fprintf(oScript,"\n");
		fputs(Line23,oScript);
		fputs(Line23b,oScript);
		fputs(Line231,oScript);fprintf(oScript,"\n");
		fputs(Line24,oScript);fprintf(oScript,"\n");

		fputs(Line25,oScript);fprintf(oScript,"\n");
		fputs(Line26,oScript);
		fputs(Line26b,oScript);
		fputs(Line26i,oScript);
		fputs(Line27i,oScript);fprintf(oScript,"\n");











		/*
		if(PrintBodyFaceSetStressPY[24] == 'i' )
        {
            fputs(Line27i,oScript);fprintf(oScript,"\n");
		}
		else
		{
            fputs(Line27,oScript);fprintf(oScript,"\n");
		}*/

		fclose(oScript);
		return 0;
	} //end print body face set stresses
int Print_Mesh(char PrintMeshPy[], char odb_dir[], char job_name[])
	{
		FILE *oScript;//output stream
		char import1[]="from abaqus import *";
		char import2[]="from abaqusConstants import *";
		char import3[]="from caeModules import *";
		char Line00[]="#";
		char Line01[]="p = mdb.models['Model-1'].parts['bitbody']";
		char Line02[]="session.viewports['Viewport: 1'].setValues(displayedObject=p)";
		char Line03[]="session.viewports['Viewport: 1'].partDisplay.setValues(mesh=ON)";
		char Line04[]="session.viewports['Viewport: 1'].partDisplay.meshOptions.setValues(";
		char Line05[]="    meshTechnique=OFF)";
		char Line06[]="session.viewports['Viewport: 1'].partDisplay.geometryOptions.setValues(";
		char Line07[]="    referenceRepresentation=ON)";
		char Line08[]="session.viewports['Viewport: 1'].view.setValues(session.views['Front'])";
		char Line09[]="set1 = mdb.models['Model-1'].parts['bitbody'].sets['body']";
		char Line10[]="leaf = dgm.LeafFromSets(sets=(set1, ))";
		char Line11[]="session.viewports['Viewport: 1'].partDisplay.displayGroup.replace(leaf=leaf)";
		char Line12[]="session.viewports['Viewport: 1'].viewportAnnotationOptions.setValues(triad=OFF,";
		char Line13[]="    legend=OFF, title=OFF, state=OFF, annotations=OFF, compass=OFF)";
		char Line14[]="session.printToFile(fileName='";
		char Line141[]="MESH_";
		char Line142[]="',";
		char Line15[]="    format=PNG, canvasObjects=(session.viewports['Viewport: 1'], ))";
		char Line16[]="session.viewports['Viewport: 1'].viewportAnnotationOptions.setValues(triad=ON,";
		char Line17[]="    legend=ON, title=ON, state=ON, annotations=ON, compass=ON)";
		char Line21[]="session.viewports['Viewport: 1'].partDisplay.setValues(mesh=OFF)";
		char Line22[]="session.viewports['Viewport: 1'].partDisplay.meshOptions.setValues(";
		char Line23[]="    meshTechnique=OFF)";
		char Line24[]="session.viewports['Viewport: 1'].partDisplay.geometryOptions.setValues(";
		char Line25[]="    referenceRepresentation=ON)";

		if ( (oScript=fopen(PrintMeshPy, "w"))==NULL)//open output file
		{
			cerr << "*** ERROR: Cannot open " << PrintMeshPy
			<< " for output." << endl;
			cin.ignore();
			cin.ignore();
			return EXIT_FAILURE;		// failure return
		} // end if
		cout<<PrintMeshPy<<"  opened for output"<<endl;
//		cout<<endl;
		fputs(import1,oScript);
		fprintf(oScript,"\n");
		fputs(import2,oScript);
		fprintf(oScript,"\n");
		fputs(import3,oScript);
		fprintf(oScript,"\n");
		fputs(Line00,oScript);fprintf(oScript,"\n");
		fputs(Line01,oScript);fprintf(oScript,"\n");
		fputs(Line02,oScript);fprintf(oScript,"\n");
		fputs(Line03,oScript);fprintf(oScript,"\n");
		fputs(Line04,oScript);fprintf(oScript,"\n");
		fputs(Line05,oScript);fprintf(oScript,"\n");
		fputs(Line06,oScript);fprintf(oScript,"\n");
		fputs(Line07,oScript);fprintf(oScript,"\n");
		fputs(Line08,oScript);fprintf(oScript,"\n");
		fputs(Line09,oScript);fprintf(oScript,"\n");
		fputs(Line10,oScript);fprintf(oScript,"\n");
		fputs(Line11,oScript);fprintf(oScript,"\n");
		fputs(Line12,oScript);fprintf(oScript,"\n");
		fputs(Line13,oScript);fprintf(oScript,"\n");
		fputs(Line14,oScript);fputs(odb_dir,oScript);
		fputs(Line141,oScript);fputs(job_name,oScript);
		fputs(Line142,oScript);fprintf(oScript,"\n");
		fputs(Line15,oScript);fprintf(oScript,"\n");
		fputs(Line16,oScript);fprintf(oScript,"\n");
		fputs(Line17,oScript);fprintf(oScript,"\n");
//		fputs(Line21,oScript);fprintf(oScript,"\n");
//		fputs(Line22,oScript);fprintf(oScript,"\n");
//		fputs(Line23,oScript);fprintf(oScript,"\n");
//		fputs(Line24,oScript);fprintf(oScript,"\n");
//		fputs(Line25,oScript);fprintf(oScript,"\n");
		fclose(oScript);
	return 0;
	}
int Print_Constraint(char PrintConstraintPy[],char odb_dir[],char job_name[],myString setRPij[18][30],
		int BladeCnt,int bladeCutCnt[200])
	{
		int I,J;
		FILE *oScript;//output stream
		char import1[]="from abaqus import *";
		char import2[]="from abaqusConstants import *";
		char import3[]="from caeModules import *";
		char Line00[]="#";
		char Line01[]="a = mdb.models['Model-1'].rootAssembly";
		char Line02[]="a.regenerate()";
		char Line03[]="session.viewports['Viewport: 1'].view.setValues(session.views['Iso'])";
		char Line031[]="session.viewports['Viewport: 1'].assemblyDisplay.setValues(loads=OFF, bcs=OFF,";
		char Line032[]="    predefinedFields=OFF, connectors=OFF, optimizationTasks=OFF,";
		char Line033[]="    geometricRestrictions=OFF, stopConditions=OFF)";
		char Line04[]="set1 = mdb.models['Model-1'].rootAssembly.allInstances['bitbody-1'].sets['body']";
		char Line05[]="leaf = dgm.LeafFromSets(sets=(set1, ))";
		char Line06[]="session.viewports['Viewport: 1'].assemblyDisplay.displayGroup.replace(";
		char Line07[]="    leaf=leaf)";
		char Line08[]="set1 = mdb.models['Model-1'].rootAssembly.sets['";
		char Line081[]="']";
		char Line09[]="leaf = dgm.LeafFromSets(sets=(set1, ))";
		char Line10[]="session.viewports['Viewport: 1'].assemblyDisplay.displayGroup.add(leaf=leaf)";
		char Line11[]="session.viewports['Viewport: 1'].setValues(displayedObject=a)";

		char Line12[]="session.viewports['Viewport: 1'].assemblyDisplay.setValues(interactions=ON,";
		char Line13[]="    constraints=ON, connectors=ON, engineeringFeatures=ON,";
		char Line14[]="    optimizationTasks=OFF, geometricRestrictions=OFF, stopConditions=OFF)";

		char Line15[]="session.viewports['Viewport: 1'].viewportAnnotationOptions.setValues(triad=OFF,";
		char Line16[]="    legend=OFF, title=OFF, state=OFF, annotations=OFF, compass=OFF)";
		char Line17[]="session.viewports['Viewport: 1'].setValues(displayedObject=a)";
		char Line18[]="session.viewports['Viewport: 1'].assemblyDisplay.setValues(step='Fn')";
		char Line19[]="session.viewports['Viewport: 1'].assemblyDisplay.setValues(mesh=OFF)";
		char Line20[]="session.printToFile(fileName='";
		char Line201[]="CSTR_";
		char Line202[]="',";
		char Line21[]="    format=PNG, canvasObjects=(session.viewports['Viewport: 1'], ))";
		char Line22[]="session.viewports['Viewport: 1'].viewportAnnotationOptions.setValues(triad=ON,";
		char Line23[]="    legend=ON, title=ON, state=ON, annotations=ON, compass=ON)";

		if ( (oScript=fopen(PrintConstraintPy, "w"))==NULL)//open output file
		{
			cerr << "*** ERROR: Cannot open " << PrintConstraintPy
			<< " for output." << endl;
			cin.ignore();
			cin.ignore();
			return EXIT_FAILURE;		// failure return
		} // end if
		cout<<PrintConstraintPy<<"  opened for output"<<endl;
//		cout<<endl;

		fputs(import1,oScript);
		fprintf(oScript,"\n");
		fputs(import2,oScript);
		fprintf(oScript,"\n");
		fputs(import3,oScript);
		fprintf(oScript,"\n");
		fputs(Line01,oScript);fprintf(oScript,"\n");
		fputs(Line02,oScript);fprintf(oScript,"\n");
		fputs(Line11,oScript);fprintf(oScript,"\n");
		fputs(Line03,oScript);fprintf(oScript,"\n");
		fputs(Line031,oScript);fprintf(oScript,"\n");
		fputs(Line032,oScript);fprintf(oScript,"\n");
		fputs(Line033,oScript);fprintf(oScript,"\n");
		fputs(Line04,oScript);fprintf(oScript,"\n");
		fputs(Line05,oScript);fprintf(oScript,"\n");
		fputs(Line06,oScript);fprintf(oScript,"\n");
		fputs(Line07,oScript);fprintf(oScript,"\n");

		for (I=0;I<BladeCnt;I++)
		{
			for (J=0;J<bladeCutCnt[I];J++)
			{
				fputs(Line00,oScript);
				fputs(setRPij[I][J].myChar,oScript);fprintf(oScript,"\n");
				fputs(Line08,oScript);fputs(setRPij[I][J].myChar,oScript);
				fputs(Line081,oScript);fprintf(oScript,"\n");
				fputs(Line09,oScript);fprintf(oScript,"\n");
				fputs(Line10,oScript);fprintf(oScript,"\n");
			}
		}
		fputs(Line11,oScript);fprintf(oScript,"\n");
		fputs(Line12,oScript);fprintf(oScript,"\n");
		fputs(Line13,oScript);fprintf(oScript,"\n");
		fputs(Line14,oScript);fprintf(oScript,"\n");
		fputs(Line15,oScript);fprintf(oScript,"\n");
		fputs(Line16,oScript);fprintf(oScript,"\n");
		fputs(Line17,oScript);fprintf(oScript,"\n");
		fputs(Line18,oScript);fprintf(oScript,"\n");
		fputs(Line19,oScript);fprintf(oScript,"\n");
		fputs(Line20,oScript);fputs(odb_dir,oScript);
		fputs(Line201,oScript);fputs(job_name,oScript);
		fputs(Line202,oScript);fprintf(oScript,"\n");
		fputs(Line21,oScript);fprintf(oScript,"\n");
		fputs(Line22,oScript);fprintf(oScript,"\n");
		fputs(Line23,oScript);fprintf(oScript,"\n");
		fclose(oScript);
		return 0;
	} //end print constraint

int Print_Load(char PrintLoadPy[],char odb_dir[],char job_name[],myString setRPij[18][30],
		int BladeCnt,int bladeCutCnt[200])
	{
		int I,J;
		FILE *oScript;//output stream
		char import1[]="from abaqus import *";
		char import2[]="from abaqusConstants import *";
		char import3[]="from caeModules import *";
		char Line00[]="#";
		char Line01[]="a = mdb.models['Model-1'].rootAssembly";
		char Line02[]="a.regenerate()";
		char Line03[]="session.viewports['Viewport: 1'].view.setValues(session.views['Iso'])";

		char Line031[]="session.viewports['Viewport: 1'].assemblyDisplay.setValues(interactions=OFF,";
		char Line032[]="    constraints=OFF, connectors=OFF, engineeringFeatures=OFF,";
		char Line033[]="    optimizationTasks=OFF, geometricRestrictions=OFF, stopConditions=OFF)";



		char Line04[]="set1 = mdb.models['Model-1'].rootAssembly.allInstances['bitbody-1'].sets['body']";
		char Line05[]="leaf = dgm.LeafFromSets(sets=(set1, ))";
		char Line06[]="session.viewports['Viewport: 1'].assemblyDisplay.displayGroup.replace(";
		char Line07[]="    leaf=leaf)";
		char Line08[]="set1 = mdb.models['Model-1'].rootAssembly.sets['";
		char Line081[]="']";
		char Line09[]="leaf = dgm.LeafFromSets(sets=(set1, ))";
		char Line10[]="session.viewports['Viewport: 1'].assemblyDisplay.displayGroup.add(leaf=leaf)";
		char Line11[]="session.viewports['Viewport: 1'].setValues(displayedObject=a)";
		char Line12[]="session.viewports['Viewport: 1'].assemblyDisplay.setValues(loads=ON, bcs=ON,";
		char Line13[]="    predefinedFields=ON, connectors=ON, optimizationTasks=OFF,";
		char Line14[]="    geometricRestrictions=OFF, stopConditions=OFF)";
		char Line15[]="session.viewports['Viewport: 1'].viewportAnnotationOptions.setValues(triad=OFF,";
		char Line16[]="    legend=OFF, title=OFF, state=OFF, annotations=OFF, compass=OFF)";
		char Line17[]="session.viewports['Viewport: 1'].setValues(displayedObject=a)";
		char Line18[]="session.viewports['Viewport: 1'].assemblyDisplay.setValues(step='Fn')";
		char Line19[]="session.viewports['Viewport: 1'].assemblyDisplay.setValues(mesh=OFF)";
		char Line20[]="session.printToFile(fileName='";
		char Line201[]="LOAD_";
		char Line202[]="',";
		char Line21[]="    format=PNG, canvasObjects=(session.viewports['Viewport: 1'], ))";
		char Line22[]="session.viewports['Viewport: 1'].viewportAnnotationOptions.setValues(triad=ON,";
		char Line23[]="    legend=ON, title=ON, state=ON, annotations=ON, compass=ON)";

		if ( (oScript=fopen(PrintLoadPy, "w"))==NULL)//open output file
		{
			cerr << "*** ERROR: Cannot open " << PrintLoadPy
			<< " for output." << endl;
			cin.ignore();
			cin.ignore();
			return EXIT_FAILURE;		// failure return
		} // end if
		cout<<PrintLoadPy<<"  opened for output"<<endl;
//		cout<<endl;

		fputs(import1,oScript);
		fprintf(oScript,"\n");
		fputs(import2,oScript);
		fprintf(oScript,"\n");
		fputs(import3,oScript);
		fprintf(oScript,"\n");
		fputs(Line01,oScript);fprintf(oScript,"\n");
		fputs(Line02,oScript);fprintf(oScript,"\n");
		fputs(Line11,oScript);fprintf(oScript,"\n");
		fputs(Line03,oScript);fprintf(oScript,"\n");
		fputs(Line031,oScript);fprintf(oScript,"\n");
		fputs(Line032,oScript);fprintf(oScript,"\n");
		fputs(Line033,oScript);fprintf(oScript,"\n");
		fputs(Line04,oScript);fprintf(oScript,"\n");
		fputs(Line05,oScript);fprintf(oScript,"\n");
		fputs(Line06,oScript);fprintf(oScript,"\n");
		fputs(Line07,oScript);fprintf(oScript,"\n");

		for (I=0;I<BladeCnt;I++)
		{
			for (J=0;J<bladeCutCnt[I];J++)
			{
				fputs(Line00,oScript);
				fputs(setRPij[I][J].myChar,oScript);fprintf(oScript,"\n");
				fputs(Line08,oScript);fputs(setRPij[I][J].myChar,oScript);
				fputs(Line081,oScript);fprintf(oScript,"\n");
				fputs(Line09,oScript);fprintf(oScript,"\n");
				fputs(Line10,oScript);fprintf(oScript,"\n");
			}
		}


		fputs(Line11,oScript);fprintf(oScript,"\n");
		fputs(Line12,oScript);fprintf(oScript,"\n");
		fputs(Line13,oScript);fprintf(oScript,"\n");
		fputs(Line14,oScript);fprintf(oScript,"\n");
		fputs(Line15,oScript);fprintf(oScript,"\n");
		fputs(Line16,oScript);fprintf(oScript,"\n");
		fputs(Line17,oScript);fprintf(oScript,"\n");
		fputs(Line18,oScript);fprintf(oScript,"\n");
		fputs(Line19,oScript);fprintf(oScript,"\n");
		fputs(Line20,oScript);fputs(odb_dir,oScript);
		fputs(Line201,oScript);fputs(job_name,oScript);
		fputs(Line202,oScript);fprintf(oScript,"\n");
		fputs(Line21,oScript);fprintf(oScript,"\n");
		fputs(Line22,oScript);fprintf(oScript,"\n");
		fputs(Line23,oScript);fprintf(oScript,"\n");
		fclose(oScript);
		return 0;
	} //end print load



int CtrPtsMatrixData(int BladeCnt,int bladeCutCnt[200],int bladeIndex[18][30],
		Point3 Pctr[200],Point3 PctrBij[18][30])//change order to blade by blade
	{
		int I,J;

		for (I=0;I<BladeCnt;I++)
		{
			for (J=0;J<bladeCutCnt[I];J++)
			{
				PctrBij[I][J].X=Pctr[bladeIndex[I][J]-1].X;
				PctrBij[I][J].Y=Pctr[bladeIndex[I][J]-1].Y;
				PctrBij[I][J].Z=Pctr[bladeIndex[I][J]-1].Z;
			}
		}
			return 0;
	}
int AssignFaceAutoSet(char autofaceset_file[],myString Pij[18][30],int BladeCnt,int bladeCutCnt[200],
	Point3 PctrBij[18][30])
	{
		//data for 3-points coordinates
		int I,J;
		//normal condition
		FILE *ocys;//output stream
		char import1[]="from abaqus import *";
		char import2[]="from abaqusConstants import *";
		char import3[]="from caeModules import *";
		char Line00[]="p = mdb.models['Model-1'].parts['bitbody']";
		char Line01[]="s = p.faces";


		char Line0[]="#";
		char Line1[]="facesDict = s.getClosest(coordinates=((";
		char Line11[]=",";
		char Line12[]=",";
		char Line13[]="),))";
		char Line20[]="key = facesDict.keys()[0]";
		char Line30[]="pointOnFace = facesDict[key][-1]";
		char Line40[]="faces = s.findAt((pointOnFace,))";
		char Line2[]="p.Set(faces=faces, name='";
		char Line21[]="')";

	if ((ocys=fopen(autofaceset_file, "w"))==NULL)//open output file
		{
			cerr << "*** ERROR: Cannot open " << autofaceset_file
			<< " for output." << endl;
			cin.ignore();
			cin.ignore();
			return EXIT_FAILURE;		// failure return
		} // end if
		cout<<autofaceset_file<<"  opened for output"<<endl;
//		cout<<endl;
		fputs(import1,ocys);fprintf(ocys,"\n");
		fputs(import2,ocys);fprintf(ocys,"\n");
		fputs(import3,ocys);fprintf(ocys,"\n");
		fprintf(ocys,"\n");
		fputs(Line00,ocys);fprintf(ocys,"\n");
		fputs(Line01,ocys);fprintf(ocys,"\n");
		fprintf(ocys,"\n");
		for (I=0;I<BladeCnt;I++)
		{
			for (J=0;J<bladeCutCnt[I];J++)
			{
				fputs(Line0,ocys);
				fputs(Pij[I][J].myChar,ocys);fprintf(ocys,"\n");
				fputs(Line1,ocys);
				fprintf(ocys,"%9.6f",PctrBij[I][J].X);
				fputs(Line11,ocys);
				fprintf(ocys,"%9.6f",PctrBij[I][J].Y);
				fputs(Line12,ocys);
				fprintf(ocys,"%9.6f",PctrBij[I][J].Z);
				fputs(Line13,ocys);fprintf(ocys,"\n");
				fputs(Line20,ocys);fprintf(ocys,"\n");
				fputs(Line30,ocys);fprintf(ocys,"\n");
				fputs(Line40,ocys);fprintf(ocys,"\n");
				fputs(Line2,ocys);
				fputs(Pij[I][J].myChar,ocys);
				fputs(Line21,ocys);fprintf(ocys,"\n");
			}
		}
		fclose(ocys);
		return 0;
	} //end WriteAutoFaceSet//******
//******************

int AssignShoulderSetAuto(char autoshoulderset_file[],char shoulderSet[],
	double BitDia)
	{
		//data for 3-points coordinates
		int I,J;
		double shankID,bodybotZ;
		double shoulderX=3.0,shoulderY=0.0,shoulderZ=-8.0;
		if(BitDia<=5.0)
		{
			shankID=2.5;
		}
		else if (BitDia<=6.0)
		{
			shankID=2.6;
		}
		else if (BitDia<=9)
		{
			shankID=3.0;
		}
		else if (BitDia<=12.0)
		{
			shankID=3.1;
			shoulderZ=-9.0;
		}
		else if (BitDia<=18.0)
		{
			shankID=3.3;
			shoulderZ=-10.0;
		}
		else if (BitDia<=24.0)
		{
			shankID=3.3;
			shoulderZ=-11.0;
		}
		else
		{
			shankID=4;
			shoulderZ=-13.0;
		}
		shoulderX=shankID+0.01;
		//normal condition
		FILE *ocys;//output stream
		char import1[]="from abaqus import *";
		char import2[]="from abaqusConstants import *";
		char import3[]="from caeModules import *";
		char Line00[]="p = mdb.models['Model-1'].parts['bitbody']";
		char Line01[]="s = p.faces";


		char Line0[]="#";
		char Line1[]="facesDict = s.getClosest(coordinates=((";
		char Line11[]=",";
		char Line12[]=",";
		char Line13[]="),))";
		char Line20[]="key = facesDict.keys()[0]";
		char Line30[]="pointOnFace = facesDict[key][-1]";
		char Line40[]="faces = s.findAt((pointOnFace,))";
		char Line2[]="p.Set(faces=faces, name='";
		char Line21[]="')";

	if ((ocys=fopen(autoshoulderset_file, "w"))==NULL)//open output file
		{
			cerr << "*** ERROR: Cannot open " << autoshoulderset_file
			<< " for output." << endl;
			cin.ignore();
			cin.ignore();
			return EXIT_FAILURE;		// failure return
		} // end if
		cout<<autoshoulderset_file<<"  opened for output"<<endl;
//		cout<<endl;
		fputs(import1,ocys);fprintf(ocys,"\n");
		fputs(import2,ocys);fprintf(ocys,"\n");
		fputs(import3,ocys);fprintf(ocys,"\n");
		fprintf(ocys,"\n");
		fputs(Line00,ocys);fprintf(ocys,"\n");
		fputs(Line01,ocys);fprintf(ocys,"\n");
		fprintf(ocys,"\n");
					fputs(Line0,ocys);
				fputs(shoulderSet,ocys);fprintf(ocys,"\n");
				fputs(Line1,ocys);
				fprintf(ocys,"%6.3f",shoulderX);
				fputs(Line11,ocys);
				fprintf(ocys,"%6.3f",shoulderY);
				fputs(Line12,ocys);
				fprintf(ocys,"%6.3f",shoulderZ);
				fputs(Line13,ocys);fprintf(ocys,"\n");
				fputs(Line20,ocys);fprintf(ocys,"\n");
				fputs(Line30,ocys);fprintf(ocys,"\n");
				fputs(Line40,ocys);fprintf(ocys,"\n");
				fputs(Line2,ocys);
				fputs(shoulderSet,ocys);
				fputs(Line21,ocys);fprintf(ocys,"\n");
		fclose(ocys);
		return 0;
	} //end autoshoulderset//******

int ReadCS_cfbfileNew(char cfa_line1[200],char cfa_line2[200],myString cutNum[200],double radius[200],
	double angArnd[200],double height[200],double prfAng[200],double bkRake[200],double sdRake[200],
	double cutDia[200],myString SizeType[200],int blade[200],int &CutNo,
	int &BladeCnt,int bladeCutCnt[18],int bladeCutNo[200],int bladeIndex[18][30],char bitcfb[20])
	{
		ifstream ics;
		int I,J;
		ics.open (bitcfb);		// ics connects to file cs_file
		if (ics.fail ())
		{
			cerr << "*** ERROR: Cannot open " << bitcfb
			<< " for input." << endl;
			cin.ignore();
			cin.ignore();
			return EXIT_FAILURE;	// failure return
		} // end if
		cout<<bitcfb<<"  opened for input"<<endl;
		I=0;
		ics.getline(cfa_line1,200,'\n');
		cout<<cfa_line1<<endl;
		ics.getline(cfa_line2,200,'\n');
		cout<<cfa_line2<<endl;
		BladeCnt=0;
		ics>>cutNum[I].myChar;
		cout<<cutNum[I].myChar<<endl;

		do
		{
			cout<<"I="<<I+1<<" ";
			ics>>radius[I]>>angArnd[I]>>height[I]>>prfAng[I]>>bkRake[I]>>sdRake[I]>>cutDia[I];
			ics>>SizeType[I].myChar>>blade[I];
			cout<<SizeType[I].myChar<<" "<<blade[I]<<endl;
//		cin>>J;

			if(blade[I]>BladeCnt)
				BladeCnt=blade[I];
			bladeCutCnt[blade[I]-1]++;
			bladeCutNo[I]=bladeCutCnt[blade[I]-1];
			bladeIndex[blade[I]-1][bladeCutNo[I]-1]=I+1;
			ics.ignore(80,'\n');
			I++;
			ics>>cutNum[I].myChar;
		}
		while(!ics.eof());
		CutNo=I;
		cout<<CutNo<<endl;
		ics.close();
		return 0;
	} //end read cfb file new

int ReadCS_desfile(char bitdes[20],char BitType[],double &bitDia,int &BladeCnt,char Bit_Profile[20],
	double &ID_Radius,double &Cone_Angle,double &Shoulder_Angle,double &Nose_Radius,double &Middle_Radius,
	double &Shoulder_Radius,double &Gage_length,double &Profile_Height,double &Nose_Location_Diameter,
	double &Outside_Dia,double cutExpture[200],int insType[200],int cutTag[200],double radius[200],
	double angArnd[200],double height[200],double prfAng[200],double bkRake[200],double sdRake[200],
	double dRadius[200],double dAngArnd[200],double dHeight[200],double dPrfAng[200],double prfAngPosi[200],
	myString SizeType[200],int blade[200],int &CutNo,int bladeCutCnt[18],int bladeCutNo[200],int bladeIndex[18][30],
	double prf_len[200],int u_pos[200],int u_bld[200],double &ConeR)
	{
		ifstream ics;
		int I,J,N,dummy,Icut;
		int NoPosition;
		int Np,u_bld0[200],insTrue=0;
		double positions0[200],radius0[200],height0[200],prfAng0[200];
		char sizeType0[20];
		double positions[200];
		int cutClmnA[200],cutClmnB[200],cutClmnF,cutClmnG;
		double cutClmnN[200];
		char readstr[30];
		char bitProf[30]="[Profile";
		int CutExist[200];
		for (I=0;I<200;I++)
		{
			CutExist[I]=0;
		}

		ics.open (bitdes);		// ics connects to file cs_file
		if (ics.fail ())
		{
			cerr << "*** ERROR: Cannot open " << bitdes
			<< " for input." << endl;
			cin.ignore();
			cin.ignore();
			return EXIT_FAILURE;	// failure return
		} // end if
		cout<<bitdes<<"  opened for input"<<endl;

//find BasicData
	do{ics>>readstr;ics.ignore(80,'\n');}
	while(!ics.eof() && strcmp (readstr,"[BasicData]") != 0);
//read BasicData
		ics>>BitType;ics.ignore(80,'\n');
		ics>>bitDia;ics.ignore(80,'\n');
		ics>>BladeCnt;ics.ignore(80,'\n');
		cout<<"BitType:"<<BitType<<endl;
		cout<<"bitDia:"<<bitDia<<endl;
		cout<<"BladeCnt:"<<BladeCnt<<endl;
//find prof_choice
	do{ics>>readstr;ics.ignore(80,'\n');}
	while(!ics.eof() && strcmp (readstr,"[profile_choice]") != 0);
//read prof_choice
		ics>>Bit_Profile;ics.ignore(80,'\n');
		cout<<"Bit Profile:"<<Bit_Profile<<endl;
//build profile search string
		strcpy (bitProf+strlen(bitProf),Bit_Profile);
		strcpy (bitProf+strlen(bitProf),"]");
//	search bitProf and read profile data
	do{ics>>readstr;ics.ignore(80,'\n');}
	while(!ics.eof() && strcmp (readstr,bitProf) != 0);

		if (strcmp (Bit_Profile,"LAG")== 0)
		{
			ics>>Cone_Angle;ics.ignore(80,'\n');
			ics>>Shoulder_Radius;ics.ignore(80,'\n');
			ics>>Gage_length;ics.ignore(80,'\n');
			ics>>Outside_Dia;ics.ignore(80,'\n');
		}
		else if (strcmp (Bit_Profile,"LAAG")== 0)
		{
			ics>>Cone_Angle;ics.ignore(80,'\n');
			ics>>Nose_Radius;ics.ignore(80,'\n');
			ics>>Shoulder_Radius;ics.ignore(80,'\n');
			ics>>Gage_length;ics.ignore(80,'\n');
			ics>>Nose_Location_Diameter;ics.ignore(80,'\n');
			ics>>Outside_Dia;ics.ignore(80,'\n');

		}
		else if (strcmp (Bit_Profile,"LAAAG")== 0)
		{
			ics>>Cone_Angle;ics.ignore(80,'\n');
			ics>>Nose_Radius;ics.ignore(80,'\n');
			ics>>Middle_Radius;ics.ignore(80,'\n');
			ics>>Shoulder_Radius;ics.ignore(80,'\n');
			ics>>Gage_length;ics.ignore(80,'\n');
			ics>>Profile_Height;ics.ignore(80,'\n');
			ics>>Nose_Location_Diameter;ics.ignore(80,'\n');
			ics>>Outside_Dia;ics.ignore(80,'\n');
		}
		else if (strcmp (Bit_Profile,"LALAG")== 0)
		{
			ics>>Cone_Angle;ics.ignore(80,'\n');
			ics>>Shoulder_Angle;ics.ignore(80,'\n');
			ics>>Nose_Radius;ics.ignore(80,'\n');
			ics>>Shoulder_Radius;ics.ignore(80,'\n');
			ics>>Gage_length;ics.ignore(80,'\n');
			ics>>Nose_Location_Diameter;ics.ignore(80,'\n');
			ics>>Outside_Dia;ics.ignore(80,'\n');
		}
		else if (strcmp (Bit_Profile,"AAAG")== 0)
		{
			ics>>ID_Radius;ics.ignore(80,'\n');
			ics>>Nose_Radius;ics.ignore(80,'\n');
			ics>>Shoulder_Radius;ics.ignore(80,'\n');
			ics>>Gage_length;ics.ignore(80,'\n');
			ics>>Nose_Location_Diameter;ics.ignore(80,'\n');
			ics>>Outside_Dia;ics.ignore(80,'\n');
		}

	do{ics>>readstr;ics.ignore(80,'\n');}
	while(!ics.eof() && strcmp (readstr,"[positions]") != 0);
	ics>>NoPosition;ics.ignore(80,'\n');
		ics>>Np;ics>>u_bld0[0];ics>>positions0[0];ics>>radius0[0];ics>>height0[0];
		ics>>prfAng0[0];ics>>sizeType0;ics.ignore(80,'\n');//read first position data
	for (I=1;I<NoPosition;I++)
	{
			ics>>Np;ics>>u_bld0[I];ics>>positions0[I];ics>>radius0[I];ics>>height0[I];
			ics>>prfAng0[I];ics>>sizeType0;ics.ignore(80,'\n');
			if (strcmp (sizeType0,"625_826_96_94")== 0||strcmp (sizeType0,"566_790_85_90")== 0)
			{
				insTrue=1;
			}
			if (fabs(prfAng0[I]-prfAng0[0])<0.001)
			{
				ConeR=radius0[I];
			}
	}
	ConeR=ConeR+0.001;
	do{ics>>readstr;ics.ignore(80,'\n');}
	while(!ics.eof() && strcmp (readstr,"[cutters]") != 0);
	ics>>NoPosition;ics.ignore(80,'\n');
//	cout<<NoPosition<<endl;
	N=0;//cutter number index
	CutNo=0;
	Icut=0;
	for (I=0;I<NoPosition;I++)
	{
		ics>>BladeCnt;ics>>positions[I];ics.ignore(80,'\n');
//	cout<<BladeCnt<<endl;
		for (J=0;J<BladeCnt;J++)
		{
			ics>>cutClmnA[N];ics>>cutClmnB[N];ics>>u_bld[N];
			ics>>blade[N];
			ics>>u_pos[N];
			ics>>cutClmnF;ics>>cutClmnG;
			if(cutClmnF==1)
			{
				if(CutExist[I]==0)
				{
					CutExist[I]=1;
				}
				u_pos[N]++;
				u_bld[N]++;
				blade[N]++;
				bladeCutCnt[blade[N]-1]++;
				bladeCutNo[N]=bladeCutCnt[blade[N]-1];
				bladeIndex[blade[N]-1][bladeCutNo[N]-1]=N;

			/* if(blade[N]==1)
				{
					u_bld[N]=blade[N];
				}
				else
				{
					u_bld[N]=BladeCnt-blade[N]+2;
				}*/
//				u_pos[N]=I+1;//did not consider vacant position
//				u_pos[N]=Icut+1;//consider vacant position
				prf_len[N]=positions[I];
				ics>>radius[N];
				ics>>height[N];
				ics>>angArnd[N];
				ics>>prfAng[N];
				ics>>bkRake[N];
				ics>>sdRake[N];
				ics>>cutClmnN[N];
				ics>>dRadius[N];
				ics>>dHeight[N];
				ics>>dAngArnd[N];
				ics>>cutExpture[N];
				if(insTrue==1)
				{
				ics>>dPrfAng[N];
				}
				prfAngPosi[N]=prfAng0[I];
				ics.ignore(80,'\n');
				ics>>SizeType[N].myChar;
				ics>>insType[N];
				ics>>cutTag[N];ics.ignore(80,'\n');
				N++;
				CutNo++;
			}
			else
			{
				ics.ignore(200,'\n');
				ics.ignore(200,'\n');
			}
		}//end loop J
		if(CutExist[I]==1)
		{
			Icut++;
		}
	}//endl loop I

		return 0;
		ics.close();
	}//end read des


	int AssignCutterDiaNew(myString SizeType[200],double cutDia[200], int CutNo)
	{
			int I;
			for(I=0;I<CutNo;I++)
			{
				if (SizeType[I].myChar[0] == '0' &&
					SizeType[I].myChar[1] == '6')
				{
					cutDia[I]=0.236;
				}
				else if (SizeType[I].myChar[0] == '0' &&
					SizeType[I].myChar[1] == '9')
				{
					cutDia[I]=0.371;
				}
				else if (SizeType[I].myChar[0] == '1' &&
					SizeType[I].myChar[1] == '1')
				{
					cutDia[I]=0.44;
				}
				else if (SizeType[I].myChar[0] == '1' &&
					SizeType[I].myChar[1] == '3')
				{
					cutDia[I]=0.529;
				}
				else if (SizeType[I].myChar[1] == '1' &&
					SizeType[I].myChar[2] == '3')
				{
					cutDia[I]=0.529;
				}
				else if (strcmp (SizeType[I].myChar,"565_790_85_90")== 0||
					strcmp (SizeType[I].myChar,"565_690_85_90")== 0)
				{
					cutDia[I]=0.565;
				}
				else if (strcmp (SizeType[I].myChar,"566_790_85_90")== 0||
					strcmp (SizeType[I].myChar,"566_690_85_90")== 0)
				{
					cutDia[I]=0.566;
				}
				else if (SizeType[I].myChar[0] == '1' &&
					SizeType[I].myChar[1] == '5')
				{
					cutDia[I]=0.575;
				}
				else if (SizeType[I].myChar[0] == '1' &&
					SizeType[I].myChar[1] == '6')
				{
					cutDia[I]=0.625;
				}
				else if (SizeType[I].myChar[1] == '1' &&
					SizeType[I].myChar[2] == '6')
				{
					cutDia[I]=0.625;
				}
				else if (strcmp (SizeType[I].myChar,"625_826_96_94")== 0)
				{
					cutDia[I]=0.625;
				}
				else if (SizeType[I].myChar[0] == '1' &&
					SizeType[I].myChar[1] == '9')
				{
					cutDia[I]=0.75;
				}
				else if (SizeType[I].myChar[1] == '1' &&
					SizeType[I].myChar[2] == '9')
				{
					cutDia[I]=0.75;
				}
				else if (SizeType[I].myChar[0] == '2' &&
					SizeType[I].myChar[1] == '2')
				{
					cutDia[I]=0.866;
				}
				else
				{
					cout<<" Please input cutter diameter of "<< SizeType[I].myChar<<": ";
					cin>>cutDia[I];
				}
			}
		return 0;
	}//end assignCutterDiaNew

	int AssignCutterLengthNew(myString SizeType[200],double cutLen[200], int CutNo)
	{
			int I;
			for(I=0;I<CutNo;I++)
			{
				if (SizeType[I].myChar[2] == '0' &&
					SizeType[I].myChar[3] == '6')
				{
					cutLen[I]=0.25;
				}
				else if (SizeType[I].myChar[2] == '0' &&
					SizeType[I].myChar[3] == '8')
				{
					cutLen[I]=0.315;
				}
				else if (SizeType[I].myChar[2] == '0' &&
					SizeType[I].myChar[3] == '9')
				{
					cutLen[I]=0.35;
				}
				else if (SizeType[I].myChar[2] == '1' &&
					SizeType[I].myChar[3] == '0')
				{
					cutLen[I]=0.394;
				}
				else if (SizeType[I].myChar[3] == '1' &&
					SizeType[I].myChar[4] == '0')
				{
					cutLen[I]=0.394;
				}
				else if (SizeType[I].myChar[2] == '1' &&
					SizeType[I].myChar[3] == '1')
				{
					cutLen[I]=0.42;
				}
				else if (SizeType[I].myChar[2] == '1' &&
					SizeType[I].myChar[3] == '3')
				{
					cutLen[I]=0.52;
				}
				else if (SizeType[I].myChar[3] == '1' &&
					SizeType[I].myChar[4] == '3')
				{
					cutLen[I]=0.52;
				}
				else if (SizeType[I].myChar[2] == '1' &&
					SizeType[I].myChar[3] == '6')
				{
					cutLen[I]=0.63;
				}
				else if (SizeType[I].myChar[3] == '1' &&
					SizeType[I].myChar[4] == '6')
				{
					cutLen[I]=0.63;
				}
				else if (SizeType[I].myChar[2] == '1' &&
					SizeType[I].myChar[3] == '7')
				{
					cutLen[I]=0.655;
				}
				else if (SizeType[I].myChar[2] == '1' &&
					SizeType[I].myChar[3] == '8')
				{
					cutLen[I]=0.7;
				}
				else if (SizeType[I].myChar[2] == '2' &&
					SizeType[I].myChar[3] == '0')
				{
					cutLen[I]=0.81;
				}
				else if (SizeType[I].myChar[3] == '2' &&
					SizeType[I].myChar[4] == '0')
				{
					cutLen[I]=0.81;
				}
				else if (SizeType[I].myChar[2] == '2' &&
					SizeType[I].myChar[3] == '2')
				{
					cutLen[I]=0.87;
				}
				else if (strcmp (SizeType[I].myChar,"566_690_85_90")== 0||
					strcmp (SizeType[I].myChar,"565_690_85_90")== 0)
				{
					cutLen[I]=0.69;

				}
				else if (strcmp (SizeType[I].myChar,"566_790_85_90")== 0||
					strcmp (SizeType[I].myChar,"565_790_85_90")== 0)
				{
					cutLen[I]=0.79;
				}
				else if (strcmp (SizeType[I].myChar,"625_826_96_94")== 0)
				{
					cutLen[I]=0.826;
				}
				else
				{
					cout<<" Please input cutter length of "<< SizeType[I].myChar<<": ";
					cin>>cutLen[I];
				}
			}
		return 0;
	}//end Assign cutter lengthNew
int WriteCS_cfbfile(char bitcfb[20],int BladeCnt,char Bit_Profile[20],
	double ID_Radius,double Cone_Angle,double Shoulder_Angle,double Nose_Radius,double Middle_Radius,
	double Shoulder_Radius,double Gage_length,double Profile_Height,double Nose_Location_Diameter,double Outside_Dia,
	double radius[200],double angArnd[200],double height[200],double prfAng[200],double prfAngPosi[200],double bkRake[200],double sdRake[200],
	myString SizeType[200],int blade[200],int CutNo,double cutDia[200])
	{

		FILE *ofcs;//output stream
		char n_u_blades[]="n_u_blades";
		int I;
		if ( (ofcs=fopen(bitcfb, "w"))==NULL)//open output file
		{
			cerr << "*** ERROR: Cannot open " << bitcfb
			<< " for output." << endl;
			cin.ignore();
			cin.ignore();
			return EXIT_FAILURE;		// failure return
		} // end if
		cout<<bitcfb<<"  opened for output"<<endl;
		fprintf(ofcs,bitcfb);fprintf(ofcs," ");fprintf(ofcs,n_u_blades);fprintf(ofcs," %2d",BladeCnt);
		fprintf(ofcs," ");fprintf(ofcs,Bit_Profile);

		if (strcmp (Bit_Profile,"LAG")== 0)
		{
	        fprintf(ofcs,"  %10.6f %10.6f %10.6f %10.6f",Cone_Angle,Shoulder_Radius,Gage_length,Outside_Dia);
		}
		else if (strcmp (Bit_Profile,"LAAG")== 0)
		{
	        fprintf(ofcs,"  %10.6f %10.6f %10.6f %10.6f %10.6f %10.6f",Cone_Angle,Nose_Radius,Shoulder_Radius,
				Gage_length,Nose_Location_Diameter,Outside_Dia);
		}
		else if (strcmp (Bit_Profile,"LAAAG")== 0)
		{
	        fprintf(ofcs,"  %10.6f %10.6f %10.6f %10.6f  %10.6f %10.6f %10.6f %10.6f",Cone_Angle,Nose_Radius,
				Middle_Radius,Shoulder_Radius,Gage_length,Profile_Height,Nose_Location_Diameter,Outside_Dia);
		}
		else if (strcmp (Bit_Profile,"LALAG")== 0)
		{
	        fprintf(ofcs,"  %10.6f %10.6f %10.6f %10.6f %10.6f %10.6f %10.6f",Cone_Angle,Shoulder_Angle,
				Nose_Radius,Shoulder_Radius,Gage_length,Nose_Location_Diameter,Outside_Dia);
		}
		else if (strcmp (Bit_Profile,"AAAG")== 0)
		{
	        fprintf(ofcs,"  %10.6f %10.6f %10.6f %10.6f %10.6f %10.6f",ID_Radius,Nose_Radius,Shoulder_Radius,
				Gage_length,Nose_Location_Diameter,Outside_Dia);
		}

		fprintf(ofcs,"\n");

		fprintf(ofcs,"cut#   radius ang arnd height prf ang bk rake sd rake cut dia size_type blade");
		fprintf(ofcs,"\n");
		for (I=0;I<CutNo;I++)
		{
			fprintf(ofcs,"%3d",I+1);
	        fprintf(ofcs,"  %9.6f %9.6f %9.6f %9.6f",radius[I],angArnd[I],height[I],prfAng[I]);
	        fprintf(ofcs," %6.3f %6.3f  %7.4f",bkRake[I],-sdRake[I],cutDia[I]);
			fprintf(ofcs,"  ");
			fprintf(ofcs,SizeType[I].myChar);
			fprintf(ofcs,"   ");
			fprintf(ofcs,"%3d",blade[I]);
			fprintf(ofcs,"\n");
		}
		fclose(ofcs);
		return 0;
	} //end write cfb: -sdRake[I]
//merge set
int body_face_dimensions3(double bitDia,double bkRake[200],double height[200],double cutDia[200],
	double &bottom1,double &bottom2,double &bottom3,double &top1,double &top2,double &top3,
	double &bodyDia1,double &bodyDia2,double &bodyDia3)// before i04
	{
		bottom1=-2.0;
		bottom2=-2.0;
		top2=-0.5;

		if (bkRake[0]>0.1)
		{
			top1=height[0]+cutDia[0]/4.0;
			top3=height[0]+cutDia[0];
			bottom3=height[0]-cutDia[0]*1.5;
		}
		else
		{
			top1=height[1]+cutDia[1]/4.0;
			top3=height[1]+cutDia[1];
			bottom3=height[1]-cutDia[1]*1.5;
		}
		if (bitDia>36.125)
		{
			bodyDia1=bitDia-2.0;//12.5
			bodyDia2=19.0;//8.0
			bodyDia3=19.0;
		}
		else if (bitDia>35.125)
		{
			bodyDia1=bitDia-2.0;//12.5
			bodyDia2=18.5;//8.0
			bodyDia3=18.5;
		}
		else if (bitDia>34.125)
		{
			bodyDia1=bitDia-2.0;//12.5
			bodyDia2=18.0;//8.0
			bodyDia3=18.0;
		}
		else if (bitDia>33.125)
		{
			bodyDia1=bitDia-2.0;//12.5
			bodyDia2=17.5;//8.0
			bodyDia3=17.5;
		}
		else if (bitDia>32.125)
		{
			bodyDia1=bitDia-2.0;//12.5
			bodyDia2=17.0;//8.0
			bodyDia3=17.0;
		}
		else if (bitDia>31.125)
		{
			bodyDia1=bitDia-2.0;//12.5
			bodyDia2=16.5;//8.0
			bodyDia3=16.5;
		}
		else if (bitDia>30.125)
		{
			bodyDia1=bitDia-2.0;//12.5
			bodyDia2=16.0;//8.0
			bodyDia3=16.0;
		}
		else if (bitDia>29.125)
		{
			bodyDia1=bitDia-2.0;//12.5
			bodyDia2=15.5;//8.0
			bodyDia3=15.5;
		}
		else if (bitDia>28.125)
		{
			bodyDia1=bitDia-2.0;//12.5
			bodyDia2=15.0;//8.0
			bodyDia3=15.0;
		}
		else if (bitDia>27.125)
		{
			bodyDia1=bitDia-2.0;//12.5
			bodyDia2=14.6;//8.0
			bodyDia3=14.6;
		}
		else if (bitDia>26.125)
		{
			bodyDia1=bitDia-2.0;//12.5
			bodyDia2=14.0;//8.0
			bodyDia3=14.0;
		}
		else if (bitDia>25.125)
		{
			bodyDia1=bitDia-2.0;//12.5
			bodyDia2=14.0;//8.0
			bodyDia3=14.0;
		}
		else if (bitDia>24.125)
		{
			bodyDia1=bitDia-2.0;//12.5
			bodyDia2=13.0;//8.0
			bodyDia3=13.0;
		}
		else if (bitDia>23.125)
		{
			bodyDia1=bitDia-2.0;//12.5
			bodyDia2=13.0;//8.0
			bodyDia3=13.0;
		}
		else if (bitDia>22.125)
		{
			bodyDia1=bitDia-2.0;//12.5
			bodyDia2=12.0;//8.0
			bodyDia3=12.0;
		}
		else if (bitDia>21.125)
		{
			bodyDia1=bitDia-2.0;//12.5
			bodyDia2=12.0;//8.0
			bodyDia3=12.0;
		}
		else if (bitDia>20.125)
		{
			bodyDia1=bitDia-2.0;//12.5
			bodyDia2=11.6;//8.0
			bodyDia3=11.6;
		}
		else if (bitDia>19.125)
		{
			bodyDia1=bitDia-2.0;//12.5
			bodyDia2=11.0;//8.0
			bodyDia3=11.0;
		}
		else if (bitDia>18.125)
		{
			bodyDia1=bitDia-2.0;//12.5
			bodyDia2=10.6;//8.0
			bodyDia3=10.6;
		}
		else if (bitDia>=17.125)
		{
			bodyDia1=bitDia-1.6;//12.5
			bodyDia2=9.6;//8.0
			bodyDia3=3.4;
		}
		else if (bitDia>=15.5)
		{
			bodyDia1=bitDia-1.6;//12.5
			bodyDia2=9.0; //7.5
			bodyDia3=9.0;
		}
		else if (bitDia>=14.5)
		{
			bodyDia1=bitDia-1.6;//12.5
			bodyDia2=9.0; //7.0
			bodyDia3=9.0;
		}
		else if (bitDia>=12.375)
		{
			bodyDia1=bitDia-1.4;//12.5
			bodyDia2=7.5;//5.5
			bodyDia3=7.5;
		}
		else if (bitDia>=11.625)
		{
			bodyDia1=bitDia-1.2;//12.5
			bodyDia2=7.0;//5.5
			bodyDia3=7.0;
		}
		else if (bitDia>=10.0)
		{
			bodyDia1=bitDia-1.0;//12.5
			bodyDia2=6.5;//4.5
			bodyDia3=6.5;
		}
		else if (bitDia>=9.5)
		{
			bodyDia1=bitDia-1.0;//12.5
			bodyDia2=5.5;//4.5
			bodyDia3=5.5;
		}
		else if (bitDia>=8.5)
		{
			bodyDia1=bitDia-1.0;//12.5
			bodyDia2=4.9;//3.9
			bodyDia3=4.9;
		}
		else if (bitDia>=7.5)
		{
			bodyDia1=bitDia-1.0;//12.5
			bodyDia2=4.3;//3.3
			bodyDia3=4.3;
		}
		else if (bitDia>=6.25)
		{
			bodyDia1=bitDia-0.8;//12.5
			bodyDia2=3.3;//2.75-3.0
			bodyDia3=3.3;
		}
		else if (bitDia>=5.125)
		{
			bodyDia1=bitDia-0.6;//12.5
			bodyDia2=3.0;//2.75
			bodyDia3=3.0;
			//steel bit needs more
		}
		else if (bitDia>=4.5)
		{
			bodyDia1=bitDia-0.6;//12.5
			bodyDia2=2.8;//2.5
			bodyDia3=2.8;
		}
		else if (bitDia>=3.625)
		{
			bodyDia1=bitDia-0.4;//12.5
			bodyDia2=2.0;//1.4
			bodyDia3=2.0;
		}
		else
		{
			bodyDia1=bitDia-0.4;//12.5
			bodyDia2=1.8;
			bodyDia3=1.8;
		}
//		bodyDia3=bodyDia1;//4.5
	return 0;
	} //end body_face_dimension3
int MergeSetNew(char mergedfaceset_file[],myString Pij[18][30],myString Bij[18][30],myString Sij[18][30],
	int BladeCnt,int bladeCutCnt[200],double bottom1,double bottom2,double bottom3,
	double top1,double top2,double top3,double bodyDia1,double bodyDia2,double bodyDia3)
	{
		int I,J;
		//normal condition
		FILE *ocys;//output stream
		char import1[]="from abaqus import *";
		char import2[]="from abaqusConstants import *";
		char import3[]="from caeModules import *";
		char Line00[]="p = mdb.models['Model-1'].parts['bitbody']";

		char Line0[]="#";
		char Line1[]="p.SetByBoolean(name='";
		char Line11[]="', sets=(p.sets['";
		char Line12[]="'], p.sets['";
		char Line13[]="'], ))";
		char Line32[]="#merge_pocket_face_set";
		char Line33[]="p.SetByBoolean(name='PocketFaces',sets=(";
		char Line35[]="    p.sets['";
		char Line351[]="'],";
		char Line36[]=" ))";
//new
		char Line01[]="p = mdb.models['Model-1'].parts['bitbody']";
		char Line02[]="s = p.faces";
//for face_set
		char Line03[]="#set1";
		char Line04[]="faces = s.getByBoundingCylinder((0.0,0.0,";
		char Line041[]="),";
		char Line05[]="(0.0,0.0,";
		char Line051[]="),";
		char Line052[]=")";
		char Line06[]="p.Set(faces=faces, name='body_face1')";
		char Line07[]="#set2";
		char Line08[]="faces = s.getByBoundingCylinder((0.0,0.0,";
		char Line081[]="),";
		char Line09[]="(0.0,0.0,";
		char Line091[]="),";
		char Line092[]=")";
		char Line10[]="p.Set(faces=faces, name='body_face2')";
		char Line107[]="#set3";
		char Line108[]="faces = s.getByBoundingCylinder((0.0,0.0,";
		char Line1081[]="),";
		char Line109[]="(0.0,0.0,";
		char Line1091[]="),";
		char Line1092[]=")";
		char Line110[]="p.Set(faces=faces, name='body_face3')";
		char Line011[]="#merge_sets";
		char Line012[]="p.SetByBoolean(name='body_face', operation=DIFFERENCE, sets=(";
		char Line013[]="    p.sets['body_face1'], p.sets['body_face2'],";
		char Line0113[]="    p.sets['body_face3'], p.sets['PocketFaces'], ))";
//endnew
	if ((ocys=fopen(mergedfaceset_file, "w"))==NULL)//open output file
		{
			cerr << "*** ERROR: Cannot open " << mergedfaceset_file
			<< " for output." << endl;
			cin.ignore();
			cin.ignore();
			return EXIT_FAILURE;		// failure return
		} // end if
		cout<<mergedfaceset_file<<"  opened for output"<<endl;
//		cout<<endl;
		fputs(import1,ocys);fprintf(ocys,"\n");
		fputs(import2,ocys);fprintf(ocys,"\n");
		fputs(import3,ocys);fprintf(ocys,"\n");
		fprintf(ocys,"\n");
		fputs(Line00,ocys);fprintf(ocys,"\n");
		fprintf(ocys,"\n");
		for (I=0;I<BladeCnt;I++)
		{
			for (J=0;J<bladeCutCnt[I];J++)
			{
				fputs(Line0,ocys);
				fputs(Pij[I][J].myChar,ocys);fprintf(ocys,"\n");
				fputs(Line1,ocys);
				fputs(Pij[I][J].myChar,ocys);
				fputs(Line11,ocys);
				fputs(Bij[I][J].myChar,ocys);
				fputs(Line12,ocys);
				fputs(Sij[I][J].myChar,ocys);
				fputs(Line13,ocys);fprintf(ocys,"\n");
			}
		}
//merge pockets
		fputs(Line32,ocys);fprintf(ocys,"\n");
		fputs(Line33,ocys);fprintf(ocys,"\n");
		for (I=0;I<BladeCnt;I++)
		{
			for (J=0;J<bladeCutCnt[I];J++)
			{
				fputs(Line35,ocys);
				fputs(Pij[I][J].myChar,ocys);
				fputs(Line351,ocys);fprintf(ocys,"\n");
			}
		}
		fputs(Line36,ocys);fprintf(ocys,"\n");
//for body_face
		fputs(Line01,ocys);fprintf(ocys,"\n");
		fputs(Line02,ocys);fprintf(ocys,"\n");
//sets
		fputs(Line03,ocys);fprintf(ocys,"\n");
		fputs(Line04,ocys);
		fprintf(ocys,"%4.2f",bottom1);
		fputs(Line041,ocys);fprintf(ocys,"\n");
		fputs(Line05,ocys);
		fprintf(ocys,"%4.2f",top1);
		fputs(Line051,ocys);
		fprintf(ocys,"%4.2f",bodyDia1/2.0);
		fputs(Line052,ocys);fprintf(ocys,"\n");
		fputs(Line06,ocys);fprintf(ocys,"\n");
//set2
		fputs(Line07,ocys);fprintf(ocys,"\n");
		fputs(Line08,ocys);
		fprintf(ocys,"%4.2f",bottom2);
		fputs(Line081,ocys);fprintf(ocys,"\n");
		fputs(Line09,ocys);
		fprintf(ocys,"%4.2f",top2);
		fputs(Line091,ocys);
		fprintf(ocys,"%4.2f",bodyDia2/2.0);
		fputs(Line092,ocys);fprintf(ocys,"\n");
		fputs(Line10,ocys);fprintf(ocys,"\n");
//set3
		fputs(Line107,ocys);fprintf(ocys,"\n");
		fputs(Line108,ocys);
		fprintf(ocys,"%4.2f",bottom3);
		fputs(Line1081,ocys);fprintf(ocys,"\n");
		fputs(Line109,ocys);
		fprintf(ocys,"%4.2f",top3);
		fputs(Line1091,ocys);
		fprintf(ocys,"%4.2f",bodyDia3/2.0);
		fputs(Line1092,ocys);fprintf(ocys,"\n");
		fputs(Line110,ocys);fprintf(ocys,"\n");
//merge sets
		fputs(Line011,ocys);fprintf(ocys,"\n");
		fputs(Line012,ocys);fprintf(ocys,"\n");
		fputs(Line013,ocys);fprintf(ocys,"\n");
		fputs(Line0113,ocys);fprintf(ocys,"\n");
		fclose(ocys);
		return 0;
	} //end mergeSetNew
//******
	int build_model_scripts(char build_model[],char py_dir[],char set_working_dir[],char cae_model0[],//force file extension
	char importStpPy[],char sectAssignPy[],char meshPartPy[],char autobotfaceset_file[],char autosidefaceset_file[],
	char mergedfaceset_file[],char cordcspy_file[],char instancePy[],char rpspy_file[],char addConstraint[],
	char Fcut10Script[],char Fn10Script[],char Fside10Script[],char autoshoulderset_file[],
	char bcFixedPy[],char FcutFnFsidePY[],char PrintMeshPy[],char PrintConstraintPy[],char PrintLoadPy[])
	{
		FILE *oScript;//output stream
		char import1[40]="from abaqus import *";
		char import2[40]="from abaqusConstants import *";
		char import3[40]="from caeModules import *";
		char Input00[]="#";
		char Input01[]="execfile('";
		char Input011[]="',";
		char Input02[]="    __main__.__dict__)";
		char Input030[]="session.viewports['Viewport: 1'].partDisplay.setValues(mesh=OFF)";
		char Input03[]="leaf = dgm.Leaf(leafType=DEFAULT_MODEL)";
		char Input04[]="session.viewports['Viewport: 1'].partDisplay.displayGroup.replace(leaf=leaf)";
		char Input05[]="session.viewports['Viewport: 1'].assemblyDisplay.setValues(loads=OFF, bcs=OFF,";
		char Input06[]="    predefinedFields=OFF, connectors=OFF)";
		char Input07[]="leaf = dgm.Leaf(leafType=DEFAULT_MODEL)";
		char Input08[]="session.viewports['Viewport: 1'].assemblyDisplay.displayGroup.replace(";
		char Input09[]="    leaf=leaf)";
		if ( (oScript=fopen(build_model, "w"))==NULL)//open output file
		{
			cerr << "*** ERROR: Cannot open " << build_model
			<< " for output." << endl;
			cin.ignore();
			cin.ignore();
			return EXIT_FAILURE;		// failure return
		} // end if
		cout<<build_model<<"  opened for output"<<endl;
//		cout<<endl;
		fputs(import1,oScript);fprintf(oScript,"\n");
		fputs(import2,oScript);fprintf(oScript,"\n");
		fputs(import3,oScript);fprintf(oScript,"\n");
//i00
		fputs(Input00,oScript);
		fputs(set_working_dir,oScript);fprintf(oScript,"\n");
		fputs(Input01,oScript);
		fputs(py_dir,oScript);
		fputs(set_working_dir,oScript);
		fputs(Input011,oScript);fprintf(oScript,"\n");
		fputs(Input02,oScript);fprintf(oScript,"\n");
//i01
		fputs(Input00,oScript);
		fputs(cae_model0,oScript);fprintf(oScript,"\n");
		fputs(Input01,oScript);
		fputs(py_dir,oScript);
		fputs(cae_model0,oScript);
		fputs(Input011,oScript);fprintf(oScript,"\n");
		fputs(Input02,oScript);fprintf(oScript,"\n");
//i02
		fputs(Input00,oScript);
		fputs(importStpPy,oScript);fprintf(oScript,"\n");
		fputs(Input01,oScript);
		fputs(py_dir,oScript);
		fputs(importStpPy,oScript);
		fputs(Input011,oScript);fprintf(oScript,"\n");
		fputs(Input02,oScript);fprintf(oScript,"\n");
//i03
		fputs(Input00,oScript);
		fputs(sectAssignPy,oScript);fprintf(oScript,"\n");
		fputs(Input01,oScript);
		fputs(py_dir,oScript);
		fputs(sectAssignPy,oScript);
		fputs(Input011,oScript);fprintf(oScript,"\n");
		fputs(Input02,oScript);fprintf(oScript,"\n");
//i04
		fputs(Input00,oScript);
		fputs(meshPartPy,oScript);fprintf(oScript,"\n");
		fputs(Input01,oScript);
		fputs(py_dir,oScript);
		fputs(meshPartPy,oScript);
		fputs(Input011,oScript);fprintf(oScript,"\n");
		fputs(Input02,oScript);fprintf(oScript,"\n");
//i05
		fputs(Input00,oScript);
		fputs(autobotfaceset_file,oScript);fprintf(oScript,"\n");
		fputs(Input01,oScript);
		fputs(py_dir,oScript);
		fputs(autobotfaceset_file,oScript);
		fputs(Input011,oScript);fprintf(oScript,"\n");
		fputs(Input02,oScript);fprintf(oScript,"\n");
//i06
		fputs(Input00,oScript);
		fputs(autosidefaceset_file,oScript);fprintf(oScript,"\n");
		fputs(Input01,oScript);
		fputs(py_dir,oScript);
		fputs(autosidefaceset_file,oScript);
		fputs(Input011,oScript);fprintf(oScript,"\n");
		fputs(Input02,oScript);fprintf(oScript,"\n");
//i07
		fputs(Input00,oScript);
		fputs(mergedfaceset_file,oScript);fprintf(oScript,"\n");
		fputs(Input01,oScript);
		fputs(py_dir,oScript);
		fputs(mergedfaceset_file,oScript);
		fputs(Input011,oScript);fprintf(oScript,"\n");
		fputs(Input02,oScript);fprintf(oScript,"\n");
//i08
		fputs(Input00,oScript);
		fputs(cordcspy_file,oScript);fprintf(oScript,"\n");
		fputs(Input01,oScript);
		fputs(py_dir,oScript);
		fputs(cordcspy_file,oScript);
		fputs(Input011,oScript);fprintf(oScript,"\n");
		fputs(Input02,oScript);fprintf(oScript,"\n");
//i09
		fputs(Input00,oScript);
		fputs(instancePy,oScript);fprintf(oScript,"\n");
		fputs(Input01,oScript);
		fputs(py_dir,oScript);
		fputs(instancePy,oScript);
		fputs(Input011,oScript);fprintf(oScript,"\n");
		fputs(Input02,oScript);fprintf(oScript,"\n");
//i10
		fputs(Input00,oScript);
		fputs(rpspy_file,oScript);fprintf(oScript,"\n");
		fputs(Input01,oScript);
		fputs(py_dir,oScript);
		fputs(rpspy_file,oScript);
		fputs(Input011,oScript);fprintf(oScript,"\n");
		fputs(Input02,oScript);fprintf(oScript,"\n");
//i11
		fputs(Input00,oScript);
		fputs(addConstraint,oScript);fprintf(oScript,"\n");
		fputs(Input01,oScript);
		fputs(py_dir,oScript);
		fputs(addConstraint,oScript);
		fputs(Input011,oScript);fprintf(oScript,"\n");
		fputs(Input02,oScript);fprintf(oScript,"\n");
//i12
		fputs(Input00,oScript);
		fputs(Fcut10Script,oScript);fprintf(oScript,"\n");
		fputs(Input01,oScript);
		fputs(py_dir,oScript);
		fputs(Fcut10Script,oScript);
		fputs(Input011,oScript);fprintf(oScript,"\n");
		fputs(Input02,oScript);fprintf(oScript,"\n");
//i13
		fputs(Input00,oScript);
		fputs(Fn10Script,oScript);fprintf(oScript,"\n");
		fputs(Input01,oScript);
		fputs(py_dir,oScript);
		fputs(Fn10Script,oScript);
		fputs(Input011,oScript);fprintf(oScript,"\n");
		fputs(Input02,oScript);fprintf(oScript,"\n");
//i14
		fputs(Input00,oScript);
		fputs(Fside10Script,oScript);fprintf(oScript,"\n");
		fputs(Input01,oScript);
		fputs(py_dir,oScript);
		fputs(Fside10Script,oScript);
		fputs(Input011,oScript);fprintf(oScript,"\n");
		fputs(Input02,oScript);fprintf(oScript,"\n");
//i15
		fputs(Input00,oScript);
		fputs(autoshoulderset_file,oScript);fprintf(oScript,"\n");
		fputs(Input01,oScript);
		fputs(py_dir,oScript);
		fputs(autoshoulderset_file,oScript);
		fputs(Input011,oScript);fprintf(oScript,"\n");
		fputs(Input02,oScript);fprintf(oScript,"\n");
//i16
		fputs(Input00,oScript);
		fputs(bcFixedPy,oScript);fprintf(oScript,"\n");
		fputs(Input01,oScript);
		fputs(py_dir,oScript);
		fputs(bcFixedPy,oScript);
		fputs(Input011,oScript);fprintf(oScript,"\n");
		fputs(Input02,oScript);fprintf(oScript,"\n");
//i17
		fputs(Input00,oScript);
		fputs(FcutFnFsidePY,oScript);fprintf(oScript,"\n");
		fputs(Input01,oScript);
		fputs(py_dir,oScript);
		fputs(FcutFnFsidePY,oScript);
		fputs(Input011,oScript);fprintf(oScript,"\n");
		fputs(Input02,oScript);fprintf(oScript,"\n");
//o01
		fputs(Input00,oScript);
		fputs(PrintMeshPy,oScript);fprintf(oScript,"\n");
		fputs(Input01,oScript);
		fputs(py_dir,oScript);
		fputs(PrintMeshPy,oScript);
		fputs(Input011,oScript);fprintf(oScript,"\n");
		fputs(Input02,oScript);fprintf(oScript,"\n");
//turn off mesh
		fputs(Input030,oScript);fprintf(oScript,"\n");
//default part display
		fputs(Input00,oScript);
		fputs("DEFAULT_DISPLAY",oScript);fprintf(oScript,"\n");
		fputs(Input03,oScript);fprintf(oScript,"\n");
		fputs(Input04,oScript);fprintf(oScript,"\n");
//o02
		fputs(Input00,oScript);
		fputs(PrintConstraintPy,oScript);fprintf(oScript,"\n");
		fputs(Input01,oScript);
		fputs(py_dir,oScript);
		fputs(PrintConstraintPy,oScript);
		fputs(Input011,oScript);fprintf(oScript,"\n");
		fputs(Input02,oScript);fprintf(oScript,"\n");
//o03
		fputs(Input00,oScript);
		fputs(PrintLoadPy,oScript);fprintf(oScript,"\n");
		fputs(Input01,oScript);
		fputs(py_dir,oScript);
		fputs(PrintLoadPy,oScript);
		fputs(Input011,oScript);fprintf(oScript,"\n");
		fputs(Input02,oScript);fprintf(oScript,"\n");
//default asembly display
		fputs(Input00,oScript);
		fputs("DEFAULT_DISPLAY",oScript);fprintf(oScript,"\n");
		fputs(Input05,oScript);fprintf(oScript,"\n");
		fputs(Input06,oScript);fprintf(oScript,"\n");
		fputs(Input07,oScript);fprintf(oScript,"\n");
		fputs(Input08,oScript);fprintf(oScript,"\n");
		fputs(Input09,oScript);fprintf(oScript,"\n");
		fclose(oScript);
	return 0;
	} //end build model
	int build_model_scriptsNew(char build_model[],char py_dir[],char set_working_dir[],char cae_model0[],//force file extension
	char importStpPy[],char sectAssignPy[],char meshPartPy[],char pocket_faceset_file[],char autobotfaceset_file[],char autosidefaceset_file[],
	char mergedfaceset_file[],char cordcspy_file[],char instancePy[],char rpspy_file[],char addConstraint[],
	char Fcut10Script[],char Fn10Script[],char Fside10Script[],char autoshoulderset_file[],
	char bcFixedPy[],char FcutFnFsidePY[],char PrintMeshPy[],char PrintConstraintPy[],char PrintLoadPy[])
	{
		FILE *oScript;//output stream
		char import1[40]="from abaqus import *";
		char import2[40]="from abaqusConstants import *";
		char import3[40]="from caeModules import *";
		char Input00[]="#";
		char Input01[]="execfile('";
		char Input011[]="',";
		char Input02[]="    __main__.__dict__)";
		char Input030[]="session.viewports['Viewport: 1'].partDisplay.setValues(mesh=OFF)";
		char Input03[]="leaf = dgm.Leaf(leafType=DEFAULT_MODEL)";
		char Input04[]="session.viewports['Viewport: 1'].partDisplay.displayGroup.replace(leaf=leaf)";
		char Input05[]="session.viewports['Viewport: 1'].assemblyDisplay.setValues(loads=OFF, bcs=OFF,";
		char Input06[]="    predefinedFields=OFF, connectors=OFF)";
		char Input07[]="leaf = dgm.Leaf(leafType=DEFAULT_MODEL)";
		char Input08[]="session.viewports['Viewport: 1'].assemblyDisplay.displayGroup.replace(";
		char Input09[]="    leaf=leaf)";
		if ( (oScript=fopen(build_model, "w"))==NULL)//open output file
		{
			cerr << "*** ERROR: Cannot open " << build_model
			<< " for output." << endl;
			cin.ignore();
			cin.ignore();
			return EXIT_FAILURE;		// failure return
		} // end if
		cout<<build_model<<"  opened for output"<<endl;
//		cout<<endl;
		fputs(import1,oScript);fprintf(oScript,"\n");
		fputs(import2,oScript);fprintf(oScript,"\n");
		fputs(import3,oScript);fprintf(oScript,"\n");
//i00
		fputs(Input00,oScript);
		fputs(set_working_dir,oScript);fprintf(oScript,"\n");
		fputs(Input01,oScript);
		fputs(py_dir,oScript);
		fputs(set_working_dir,oScript);
		fputs(Input011,oScript);fprintf(oScript,"\n");
		fputs(Input02,oScript);fprintf(oScript,"\n");
//i01
		fputs(Input00,oScript);
		fputs(cae_model0,oScript);fprintf(oScript,"\n");
		fputs(Input01,oScript);
		fputs(py_dir,oScript);
		fputs(cae_model0,oScript);
		fputs(Input011,oScript);fprintf(oScript,"\n");
		fputs(Input02,oScript);fprintf(oScript,"\n");
//i02
		fputs(Input00,oScript);
		fputs(importStpPy,oScript);fprintf(oScript,"\n");
		fputs(Input01,oScript);
		fputs(py_dir,oScript);
		fputs(importStpPy,oScript);
		fputs(Input011,oScript);fprintf(oScript,"\n");
		fputs(Input02,oScript);fprintf(oScript,"\n");
//i03
		fputs(Input00,oScript);
		fputs(sectAssignPy,oScript);fprintf(oScript,"\n");
		fputs(Input01,oScript);
		fputs(py_dir,oScript);
		fputs(sectAssignPy,oScript);
		fputs(Input011,oScript);fprintf(oScript,"\n");
		fputs(Input02,oScript);fprintf(oScript,"\n");
//i04
		fputs(Input00,oScript);
		fputs(meshPartPy,oScript);fprintf(oScript,"\n");
		fputs(Input01,oScript);
		fputs(py_dir,oScript);
		fputs(meshPartPy,oScript);
		fputs(Input011,oScript);fprintf(oScript,"\n");
		fputs(Input02,oScript);fprintf(oScript,"\n");
//i07new
		fputs(Input00,oScript);
		fputs(pocket_faceset_file,oScript);fprintf(oScript,"\n");
		fputs(Input01,oScript);
		fputs(py_dir,oScript);
		fputs(pocket_faceset_file,oScript);
		fputs(Input011,oScript);fprintf(oScript,"\n");
		fputs(Input02,oScript);fprintf(oScript,"\n");
//i08
		fputs(Input00,oScript);
		fputs(cordcspy_file,oScript);fprintf(oScript,"\n");
		fputs(Input01,oScript);
		fputs(py_dir,oScript);
		fputs(cordcspy_file,oScript);
		fputs(Input011,oScript);fprintf(oScript,"\n");
		fputs(Input02,oScript);fprintf(oScript,"\n");
//i09
		fputs(Input00,oScript);
		fputs(instancePy,oScript);fprintf(oScript,"\n");
		fputs(Input01,oScript);
		fputs(py_dir,oScript);
		fputs(instancePy,oScript);
		fputs(Input011,oScript);fprintf(oScript,"\n");
		fputs(Input02,oScript);fprintf(oScript,"\n");
//i10
		fputs(Input00,oScript);
		fputs(rpspy_file,oScript);fprintf(oScript,"\n");
		fputs(Input01,oScript);
		fputs(py_dir,oScript);
		fputs(rpspy_file,oScript);
		fputs(Input011,oScript);fprintf(oScript,"\n");
		fputs(Input02,oScript);fprintf(oScript,"\n");
//i11
		fputs(Input00,oScript);
		fputs(addConstraint,oScript);fprintf(oScript,"\n");
		fputs(Input01,oScript);
		fputs(py_dir,oScript);
		fputs(addConstraint,oScript);
		fputs(Input011,oScript);fprintf(oScript,"\n");
		fputs(Input02,oScript);fprintf(oScript,"\n");
//i12
		fputs(Input00,oScript);
		fputs(Fcut10Script,oScript);fprintf(oScript,"\n");
		fputs(Input01,oScript);
		fputs(py_dir,oScript);
		fputs(Fcut10Script,oScript);
		fputs(Input011,oScript);fprintf(oScript,"\n");
		fputs(Input02,oScript);fprintf(oScript,"\n");
//i13
		fputs(Input00,oScript);
		fputs(Fn10Script,oScript);fprintf(oScript,"\n");
		fputs(Input01,oScript);
		fputs(py_dir,oScript);
		fputs(Fn10Script,oScript);
		fputs(Input011,oScript);fprintf(oScript,"\n");
		fputs(Input02,oScript);fprintf(oScript,"\n");
//i14
		fputs(Input00,oScript);
		fputs(Fside10Script,oScript);fprintf(oScript,"\n");
		fputs(Input01,oScript);
		fputs(py_dir,oScript);
		fputs(Fside10Script,oScript);
		fputs(Input011,oScript);fprintf(oScript,"\n");
		fputs(Input02,oScript);fprintf(oScript,"\n");
//i15
		fputs(Input00,oScript);
		fputs(autoshoulderset_file,oScript);fprintf(oScript,"\n");
		fputs(Input01,oScript);
		fputs(py_dir,oScript);
		fputs(autoshoulderset_file,oScript);
		fputs(Input011,oScript);fprintf(oScript,"\n");
		fputs(Input02,oScript);fprintf(oScript,"\n");
//i16
		fputs(Input00,oScript);
		fputs(bcFixedPy,oScript);fprintf(oScript,"\n");
		fputs(Input01,oScript);
		fputs(py_dir,oScript);
		fputs(bcFixedPy,oScript);
		fputs(Input011,oScript);fprintf(oScript,"\n");
		fputs(Input02,oScript);fprintf(oScript,"\n");
//i17
		fputs(Input00,oScript);
		fputs(FcutFnFsidePY,oScript);fprintf(oScript,"\n");
		fputs(Input01,oScript);
		fputs(py_dir,oScript);
		fputs(FcutFnFsidePY,oScript);
		fputs(Input011,oScript);fprintf(oScript,"\n");
		fputs(Input02,oScript);fprintf(oScript,"\n");
//o01
		fputs(Input00,oScript);
		fputs(PrintMeshPy,oScript);fprintf(oScript,"\n");
		fputs(Input01,oScript);
		fputs(py_dir,oScript);
		fputs(PrintMeshPy,oScript);
		fputs(Input011,oScript);fprintf(oScript,"\n");
		fputs(Input02,oScript);fprintf(oScript,"\n");
//turn off mesh
		fputs(Input030,oScript);fprintf(oScript,"\n");
//default part display
		fputs(Input00,oScript);
		fputs("DEFAULT_DISPLAY",oScript);fprintf(oScript,"\n");
		fputs(Input03,oScript);fprintf(oScript,"\n");
		fputs(Input04,oScript);fprintf(oScript,"\n");
//o02
		fputs(Input00,oScript);
		fputs(PrintConstraintPy,oScript);fprintf(oScript,"\n");
		fputs(Input01,oScript);
		fputs(py_dir,oScript);
		fputs(PrintConstraintPy,oScript);
		fputs(Input011,oScript);fprintf(oScript,"\n");
		fputs(Input02,oScript);fprintf(oScript,"\n");
//o03
		fputs(Input00,oScript);
		fputs(PrintLoadPy,oScript);fprintf(oScript,"\n");
		fputs(Input01,oScript);
		fputs(py_dir,oScript);
		fputs(PrintLoadPy,oScript);
		fputs(Input011,oScript);fprintf(oScript,"\n");
		fputs(Input02,oScript);fprintf(oScript,"\n");
//default asembly display
		fputs(Input00,oScript);
		fputs("DEFAULT_DISPLAY",oScript);fprintf(oScript,"\n");
		fputs(Input05,oScript);fprintf(oScript,"\n");
		fputs(Input06,oScript);fprintf(oScript,"\n");
		fputs(Input07,oScript);fprintf(oScript,"\n");
		fputs(Input08,oScript);fprintf(oScript,"\n");
		fputs(Input09,oScript);fprintf(oScript,"\n");
		fclose(oScript);
	return 0;
	} //end build model new
int FindingPocketFaceSet(char find_pocket_set_file[],char py_dir[],char autobotfaceset_file[],char autosidefaceset_file[],char mergedfaceset_file[])
	{

		FILE *oScript;//output stream
		char import1[40]="from abaqus import *";
		char import2[40]="from abaqusConstants import *";
		char import3[40]="from caeModules import *";
		char Input00[]="#";
		char Input01[]="execfile('";
		char Input011[]="',";
		char Input02[]="    __main__.__dict__)";

		char Line01[]="a = mdb.models['Model-1'].rootAssembly";
		char Line02[]="a.regenerate()";
		char Line03[]="session.viewports['Viewport: 1'].setValues(displayedObject=a)";

		if ( (oScript=fopen(find_pocket_set_file, "w"))==NULL)//open output file
		{
			cerr << "*** ERROR: Cannot open " << find_pocket_set_file
			<< " for output." << endl;
			cin.ignore();
			cin.ignore();
			return EXIT_FAILURE;		// failure return
		} // end if
		cout<<find_pocket_set_file<<"  opened for output"<<endl;
		cout<<endl;
		fputs(import1,oScript);fprintf(oScript,"\n");
		fputs(import2,oScript);fprintf(oScript,"\n");
		fputs(import3,oScript);fprintf(oScript,"\n");
//i05a
		fputs(Input00,oScript);
		fputs(autobotfaceset_file,oScript);fprintf(oScript,"\n");
		fputs(Input01,oScript);
		fputs(py_dir,oScript);
		fputs(autobotfaceset_file,oScript);
		fputs(Input011,oScript);fprintf(oScript,"\n");
		fputs(Input02,oScript);fprintf(oScript,"\n");
//i05b
		fputs(Input00,oScript);
		fputs(autosidefaceset_file,oScript);fprintf(oScript,"\n");
		fputs(Input01,oScript);
		fputs(py_dir,oScript);
		fputs(autosidefaceset_file,oScript);
		fputs(Input011,oScript);fprintf(oScript,"\n");
		fputs(Input02,oScript);fprintf(oScript,"\n");
//i05c
		fputs(Input00,oScript);
		fputs(mergedfaceset_file,oScript);fprintf(oScript,"\n");
		fputs(Input01,oScript);
		fputs(py_dir,oScript);
		fputs(mergedfaceset_file,oScript);
		fputs(Input011,oScript);fprintf(oScript,"\n");
		fputs(Input02,oScript);fprintf(oScript,"\n");
		fclose(oScript);
	return 0;
	} //end FindingPocketFaceSet

int WriteCS_cfb_cfbfile(char bitcfb[20],char cfa_line1[200],char cfa_line2[200],
	double radius[200],double angArnd[200],double height[200],double prfAng[200],double bkRake[200],
	double sdRake[200],myString SizeType[200],int blade[200],int CutNo,double cutDia[200])
	{
		FILE *ofcs;//output stream
		char n_u_blades[]="n_u_blades";
		int I;
		if ( (ofcs=fopen(bitcfb, "w"))==NULL)//open output file
		{
			cerr << "*** ERROR: Cannot open " << bitcfb
			<< " for output." << endl;
			cin.ignore();
			cin.ignore();
			return EXIT_FAILURE;		// failure return
		} // end if
		cout<<bitcfb<<"  opened for output"<<endl;
		fprintf(ofcs,cfa_line1);fprintf(ofcs,"\n");
		fprintf(ofcs,cfa_line2);fprintf(ofcs,"\n");
		for (I=0;I<CutNo;I++)
		{
			fprintf(ofcs,"%3d",I+1);
	        fprintf(ofcs," %9.6f %11.6f %9.6f %10.6f",radius[I],angArnd[I],height[I],prfAng[I]);
	        fprintf(ofcs," %6.3f %6.3f %7.4f",bkRake[I],-sdRake[I],cutDia[I]);
			fprintf(ofcs," ");
			fprintf(ofcs,SizeType[I].myChar);
			fprintf(ofcs," ");
			fprintf(ofcs,"%3d",blade[I]);
			fprintf(ofcs,"\n");
		}
		fclose(ofcs);
		return 0;
	} //end write cfb from reading cfb
//*****New
int IndexPrimaryCutters(int CutNo,int BladeCnt,int bladeCutCnt[18],int bladeIndex[18][30],int u_bld[200],
		int bladePtag[200],int bladePtmp[200])
	{
		int I,J;
		int u_bldN,BladePN;
		BladePN=0;
		u_bldN=0;
		for(I=0;I<CutNo;I++)
		{
			bladePtmp[I]=0;
			bladePtag[I]=0;
		}
		for(I=0;I<BladeCnt;I++)
		{
			if(u_bld[bladeIndex[I][0]-1]!=u_bldN)
			{
				BladePN++;
				for (J=0;J<bladeCutCnt[I];J++)
				{
					bladePtmp[bladeIndex[I][J]-1]=BladePN;
					bladePtag[bladeIndex[I][J]-1]=1;
				}
				u_bldN=u_bld[bladeIndex[I][0]-1];
			}
		}
		return 0;
	} //end primary cutter
int GetPrimaryCutters(double radius[200],double angArnd[200],double height[200],double prfAng[200],double bkRake[200],
	double sdRake[200],double cutDia[200],myString SizeType[200],int bladePtmp[200],double cutLen[200],int bladePtag[200],
	int CutNo,double radiusP[200],double angArndP[200],double heightP[200],double prfAngP[200],double bkRakeP[200],
	double sdRakeP[200],double cutDiaP[200],myString SizeTypeP[200],int bladeP[200],double cutLenP[200],int &CutNoP,
	int &BladeCntP,int bladeCutCntP[18],int bladeCutNoP[200],int bladeIndexP[18][30])
	{
		int I,IP;
		IP=0;
		BladeCntP=0;
		for(I=0;I<CutNo;I++)
		{
			if (bladePtag[I]==1)
			{
				radiusP[IP]=radius[I];
				angArndP[IP]=angArnd[I];
				heightP[IP]=height[I];
				prfAngP[IP]=prfAng[I];
				bkRakeP[IP]=bkRake[I];
				sdRakeP[IP]=sdRake[I];
				strcpy(SizeTypeP[IP].myChar,SizeType[I].myChar);
				cutDiaP[IP]=cutDia[I];
				cutLenP[IP]=cutLen[I];
				bladeP[IP]=bladePtmp[I];
				if(bladeP[IP]>BladeCntP)
					BladeCntP=bladeP[IP];
				bladeCutCntP[bladeP[IP]-1]++;
				bladeCutNoP[IP]=bladeCutCntP[bladeP[IP]-1];
				bladeIndexP[bladeP[IP]-1][bladeCutNoP[IP]-1]=IP+1;
				IP++;
			}
		}
		CutNoP=IP;
		return 0;
	} //end primary cutter
int GetPrimaryBladeDeltaAngle(double radiusP[200],double angArndP[200],double heightP[200],double cutDiaP[200],
	int bladeP[200],int BladeCntP,int bladeCutCntP[18],int bladeIndexP[18][30],int bladeAngP[9],int dBladeAngP[9],
	double BLadeTipCutDia[9],double BLadeTipHeight[9],double BLadeTipRadius[9],int BladeRotAng[10])
	{
		int I,RotSum;
//for I=0
		if (radiusP[0]>0.2)//not central stinger
		{
			BLadeTipRadius[0]=radiusP[bladeIndexP[0][0]-1];
			BLadeTipHeight[0]=heightP[bladeIndexP[0][0]-1];
			BLadeTipCutDia[0]=cutDiaP[bladeIndexP[0][0]-1];
			bladeAngP[0]=int(angArndP[bladeIndexP[0][0]-1]);
		}
		else // central stinger
		{
			BLadeTipRadius[0]=radiusP[bladeIndexP[0][1]-1];
			BLadeTipHeight[0]=heightP[bladeIndexP[0][1]-1];
			BLadeTipCutDia[0]=cutDiaP[bladeIndexP[0][1]-1];
			bladeAngP[0]=int(angArndP[bladeIndexP[0][1]-1]);
		}
		for (I=1;I<BladeCntP;I++)
		{
			BLadeTipRadius[I]=radiusP[bladeIndexP[I][0]-1];
			BLadeTipHeight[I]=heightP[bladeIndexP[I][0]-1];
			BLadeTipCutDia[I]=cutDiaP[bladeIndexP[I][0]-1];
			bladeAngP[I]=int(angArndP[bladeIndexP[I][0]-1]);
		}
		BladeRotAng[0]=-bladeAngP[0];
		RotSum=BladeRotAng[0];
		for (I=1;I<BladeCntP;I++)
		{
			if(bladeAngP[I-1]>bladeAngP[I])
			{
			 BladeRotAng[I]=bladeAngP[I-1]-bladeAngP[I];
			}
			else
			{
			 BladeRotAng[I]=bladeAngP[I-1]-bladeAngP[I]+360;
			}
			RotSum=RotSum+BladeRotAng[I];
		}
		BladeRotAng[BladeCntP]=360-RotSum;
		if(BladeRotAng[BladeCntP]>360)
		{
			BladeRotAng[BladeCntP]=BladeRotAng[BladeCntP]-360;
		}
//find delta angle between last blade and first blade
		if(bladeAngP[BladeCntP-1]>bladeAngP[0])
		{
			dBladeAngP[0]=bladeAngP[BladeCntP-1]-bladeAngP[0];
		}
		else
		{
			dBladeAngP[0]=bladeAngP[BladeCntP-1]-bladeAngP[0]+360;
		}
//find delta angles for other blades
		for (I=1;I<BladeCntP;I++)
		{
			if(bladeAngP[I-1]>bladeAngP[I])
			{
			 dBladeAngP[I]=bladeAngP[I-1]-bladeAngP[I];
			}
			else
			{
			 dBladeAngP[I]=bladeAngP[I-1]-bladeAngP[I]+360;
			}
		}
		return 0;
	} //end get primary blade delta angle
int LocateBladeFacesByCylinder(char bladeface_file[15],int BladeCntP,double bitDia,
	double BLadeTipCutDia[9],double BLadeTipHeight[9],double BLadeTipRadius[9],int bladeAngP[10],int dBladeAngP[10],
	double bottom1,double bottom2,double top1,double top2,double bodyDia1,double bodyDia2)
	{
		double Xib[9],Yib[9],Zib[9],Xit[9],Yit[9],Zit[9],Ri[9],dummy;
		double Xob[9],Yob[9],Zob[9],Xot[9],Yot[9],Zot[9],Ro[9];
		double pi=3.141592654;
		double MultiI=0.0,MultiO=0.2;
		int bladeSlotAngI[10],bladeSlotAngO[10];
		//data for 3-points coordinates
		int I;
		myString Blade[9],BladeI[9],BladeO[9];
		strcpy(Blade[0].myChar,"blade1");
		strcpy(Blade[1].myChar,"blade2");
		strcpy(Blade[2].myChar,"blade3");
		strcpy(Blade[3].myChar,"blade4");
		strcpy(Blade[4].myChar,"blade5");
		strcpy(Blade[5].myChar,"blade6");
		strcpy(Blade[6].myChar,"blade7");
		strcpy(Blade[7].myChar,"blade8");
		strcpy(Blade[8].myChar,"blade9");
		strcpy(BladeI[0].myChar,"blade1i");
		strcpy(BladeI[1].myChar,"blade2i");
		strcpy(BladeI[2].myChar,"blade3i");
		strcpy(BladeI[3].myChar,"blade4i");
		strcpy(BladeI[4].myChar,"blade5i");
		strcpy(BladeI[5].myChar,"blade6i");
		strcpy(BladeI[6].myChar,"blade7i");
		strcpy(BladeI[7].myChar,"blade8i");
		strcpy(BladeI[8].myChar,"blade9i");
		strcpy(BladeO[0].myChar,"blade1o");
		strcpy(BladeO[1].myChar,"blade2o");
		strcpy(BladeO[2].myChar,"blade3o");
		strcpy(BladeO[3].myChar,"blade4o");
		strcpy(BladeO[4].myChar,"blade5o");
		strcpy(BladeO[5].myChar,"blade6o");
		strcpy(BladeO[6].myChar,"blade7o");
		strcpy(BladeO[7].myChar,"blade8o");
		strcpy(BladeO[8].myChar,"blade9o");

		for (I=0;I<BladeCntP;I++)
		{
			 bladeSlotAngI[I]=int(bladeAngP[I]+dBladeAngP[I]*MultiI);
			if(bladeSlotAngI[I]>360)
			{
			 bladeSlotAngI[I]=bladeSlotAngI[I]-360;
			}

			bladeSlotAngO[I]=int(bladeAngP[I]+dBladeAngP[I]*MultiO);
			if(bladeSlotAngO[I]>360)
			{
			 bladeSlotAngO[I]=bladeSlotAngO[I]-360;
			}
		}
		for(I=0;I<BladeCntP;I++)
		{
			if(BLadeTipRadius[I]>1.5)
			{
				Xib[I]=(BLadeTipRadius[I]-0.5)*cos(bladeSlotAngI[I]*pi/180.0);
				Yib[I]=(BLadeTipRadius[I]-0.5)*sin(bladeSlotAngI[I]*pi/180.0);
				Zib[I]=-0.5;
				Xit[I]=Xib[I];
				Yit[I]=Yib[I];
				Zit[I]=BLadeTipHeight[I]-BLadeTipCutDia[I]*1.5;
				Ri[I]=1.0;
			}
			else if(BLadeTipRadius[I]>1.0)
			{
			Xib[I]=(BLadeTipRadius[I]-0.25)*cos(bladeSlotAngI[I]*pi/180.0);
			Yib[I]=(BLadeTipRadius[I]-0.25)*sin(bladeSlotAngI[I]*pi/180.0);
			Zib[I]=-0.5;
			Xit[I]=Xib[I];
			Yit[I]=Yib[I];
			Zit[I]=BLadeTipHeight[I]-BLadeTipCutDia[I]*1.5;
			Ri[I]=0.75;
			}
			else if(BLadeTipRadius[I]>0.75)
			{
				Xib[I]=(BLadeTipRadius[I]-0.15)*cos(bladeSlotAngI[I]*pi/180.0);
				Yib[I]=(BLadeTipRadius[I]-0.15)*sin(bladeSlotAngI[I]*pi/180.0);
				Zib[I]=-0.5;
				Xit[I]=Xib[I];
				Yit[I]=Yib[I];
				Zit[I]=BLadeTipHeight[I]-BLadeTipCutDia[I]*0.6;
				Ri[I]=0.7;
			}
			else if(BLadeTipRadius[I]>0.5)
			{
				Xib[I]=(BLadeTipRadius[I]-0.05)*cos(bladeSlotAngI[I]*pi/180.0);
				Yib[I]=(BLadeTipRadius[I]-0.05)*sin(bladeSlotAngI[I]*pi/180.0);
				Zib[I]=-0.5;
				Xit[I]=Xib[I];
				Yit[I]=Yib[I];
				Zit[I]=BLadeTipHeight[I]-BLadeTipCutDia[I]*0.6;
				Ri[I]=0.6;
			}
			else
			{
				Xib[I]=(BLadeTipRadius[I]-0.0)*cos(bladeSlotAngI[I]*pi/180.0);
				Yib[I]=(BLadeTipRadius[I]-0.0)*sin(bladeSlotAngI[I]*pi/180.0);
				Zib[I]=-0.5;
				Xit[I]=Xib[I];
				Yit[I]=Yib[I];
				Zit[I]=BLadeTipHeight[I]-BLadeTipCutDia[I]*0.6;
				Ri[I]=0.45;
			}
			Xob[I]=(BLadeTipRadius[I]*0.0+bitDia*0.5)/2.0*cos(bladeSlotAngO[I]*pi/180.0); Xot[I]=Xob[I];
			Yob[I]=(BLadeTipRadius[I]*0.0+bitDia*0.5)/2.0*sin(bladeSlotAngO[I]*pi/180.0); Yot[I]=Yob[I];
			Zob[I]=-2.0; Zot[I]=BLadeTipHeight[I]-BLadeTipCutDia[I]*1.0;
//			Ro[I]=bitDia*0.25*dBladeAngP[I]/90.0;
			Ro[I]=(bitDia-1.0)/4.0*5.0/BladeCntP;
		}
		//normal condition
		FILE *ocys;//output stream
		char import1[]="from abaqus import *";
		char import2[]="from abaqusConstants import *";
		char import3[]="from caeModules import *";
		char BLine01[]="p = mdb.models['Model-1'].parts['bitbody']";
		char BLine02[]="s = p.faces";
//********
		char BLine0[]="#";
		char BLine1[]="side1Faces = s.getByBoundingCylinder((";
		char BLine11[]=",";
		char BLine12[]=",";
		char BLine13[]="),";
		char BLine2[]="(";
		char BLine21[]=",";
		char BLine22[]=",";
		char BLine23[]="),";
		char BLine24[]=")";
		char BLine3[]="p.Surface(side1Faces=side1Faces, name='";
		char BLine31[]="')";
		char BLineSet0[]="#Set";
		char BLineSet1[]="faces = s.getByBoundingCylinder((";
		char BLineSet11[]=",";
		char BLineSet12[]=",";
		char BLineSet13[]="),";
		char BLineSet14[]=",";
		char BLineSet15[]=",";
		char BLineSet16[]=")";
		char BLineSet2[]="(";
		char BLineSet21[]=",";
		char BLineSet22[]=",";
		char BLineSet23[]="),";
		char BLineSet24[]=")";
		char BLineSet3[]="p.Set(faces=faces, name='";
		char BLineSet31[]="')";
//for core surface
//for face_set
		char BLine007[]="#core_set";
		char BLine008[]="faces = s.getByBoundingCylinder((0.0,0.0,";
		char BLine0081[]="),";
		char BLine009[]="(0.0,0.0,";
		char BLine0091[]="),";
		char BLine0092[]=")";
		char BLine010[]="p.Set(faces=faces, name='core_face')";
		char BLine011[]="#merge_";
		char BLine012[]="p.SetByBoolean(name='";
		char BLine0121[]="', operation=DIFFERENCE, sets=(";
		char BLine013[]="    p.sets['";
		char BLine0131[]="'], p.sets['core_face'], ))";
//for faces
		char BLine027[]="#core_face";
		char BLine028[]="side1Faces1 = s.getByBoundingCylinder((0.0,0.0,";
		char BLine0281[]="),";
		char BLine029[]="(0.0,0.0,";
		char BLine0291[]="),";
		char BLine0292[]=")";
		char BLine030[]="p.Surface(side1Faces=side1Faces1, name='core_face')";
		char BLine031[]="#merge_";
		char BLine032[]="p.SurfaceByBoolean(name='";
		char BLine0321[]="', operation=DIFFERENCE, surfaces=(";
		char BLine033[]="    p.surfaces['";
		char BLine0331[]="'], p.surfaces['core_face'], ))";

		char BLine001[]="#delete face";
		char BLine0010[]="del mdb.models['Model-1'].parts['bitbody'].surfaces['";
		char BLine0011[]="']";

		char BLine002[]="#delete set";
		char BLine0020[]="del mdb.models['Model-1'].parts['bitbody'].sets['";
		char BLine0021[]="']";

		char BLine003[]="#rename faces";
		char BLine0030[]="mdb.models['Model-1'].parts['bitbody'].surfaces.changeKey(fromName='";
		char BLine0031[]="',";
		char BLine0040[]="    toName='";
		char BLine0041[]="')";

		if ((ocys=fopen(bladeface_file, "w"))==NULL)//open output file
		{
			cerr << "*** ERROR: Cannot open " << bladeface_file
			<< " for output." << endl;
			cin.ignore();
			cin.ignore();
			return EXIT_FAILURE;		// failure return
		} // end if
		cout<<bladeface_file<<"  opened for output"<<endl;
		cout<<endl;
		fputs(import1,ocys);fprintf(ocys,"\n");
		fputs(import2,ocys);fprintf(ocys,"\n");
		fputs(import3,ocys);fprintf(ocys,"\n");
		fprintf(ocys,"\n");
		fputs(BLine01,ocys);fprintf(ocys,"\n");
		fputs(BLine02,ocys);fprintf(ocys,"\n");
		fprintf(ocys,"\n");
		for (I=0;I<BladeCntP;I++)//surfaces
		{
				fputs(BLine0,ocys);
				fputs(BladeI[I].myChar,ocys);fprintf(ocys,"\n");

				fputs(BLine1,ocys);
				fprintf(ocys,"%5.2f",Xib[I]);fputs(BLine11,ocys);
				fprintf(ocys,"%5.2f",Yib[I]);fputs(BLine12,ocys);
				fprintf(ocys,"%5.2f",Zib[I]);fputs(BLine13,ocys);
				fprintf(ocys,"\n");
				fputs(BLine2,ocys);
				fprintf(ocys,"%5.2f",Xit[I]);fputs(BLine21,ocys);
				fprintf(ocys,"%5.2f",Yit[I]);fputs(BLine22,ocys);
				fprintf(ocys,"%5.2f",Zit[I]);fputs(BLine23,ocys);
				fprintf(ocys,"%5.2f",Ri[I]);fputs(BLine24,ocys);
				fprintf(ocys,"\n");
				fputs(BLine3,ocys);
				fputs(BladeI[I].myChar,ocys);
				fputs(BLine31,ocys);fprintf(ocys,"\n");
				fputs(BLine0,ocys);
				fputs(BladeO[I].myChar,ocys);fprintf(ocys,"\n");
				fputs(BLine1,ocys);
				fprintf(ocys,"%5.2f",Xob[I]);fputs(BLine11,ocys);
				fprintf(ocys,"%5.2f",Yob[I]);fputs(BLine12,ocys);
				fprintf(ocys,"%5.2f",Zob[I]);fputs(BLine13,ocys);
				fprintf(ocys,"\n");
				fputs(BLine2,ocys);
				fprintf(ocys,"%5.2f",Xot[I]);fputs(BLine21,ocys);
				fprintf(ocys,"%5.2f",Yot[I]);fputs(BLine22,ocys);
				fprintf(ocys,"%5.2f",Zot[I]);fputs(BLine23,ocys);
				fprintf(ocys,"%5.2f",Ro[I]);fputs(BLine24,ocys);
				fprintf(ocys,"\n");
				fputs(BLine3,ocys);
				fputs(BladeO[I].myChar,ocys);
				fputs(BLine31,ocys);fprintf(ocys,"\n");
		}
				fputs(BLine0,ocys);fprintf(ocys,"\n");
//core face
				fputs(BLine027,ocys);fprintf(ocys,"\n");
				fputs(BLine028,ocys);
				fprintf(ocys,"%4.2f",bottom2);
				fputs(BLine0281,ocys);fprintf(ocys,"\n");
				fputs(BLine029,ocys);
				fprintf(ocys,"%4.2f",top1);
				fputs(BLine0291,ocys);
				fprintf(ocys,"%4.2f",bodyDia2/2.0);
				fputs(BLine0292,ocys);fprintf(ocys,"\n");
				fputs(BLine030,ocys);fprintf(ocys,"\n");
			for (I=0;I<BladeCntP;I++)//surfaces
			{
					fputs(BLine031,ocys);fputs(Blade[I].myChar,ocys);fprintf(ocys,"\n");
					fputs(BLine032,ocys);
					fputs(Blade[I].myChar,ocys);
					fputs(BLine0321,ocys);fprintf(ocys,"\n");
					fputs(BLine033,ocys);
					fputs(BladeO[I].myChar,ocys);
					fputs(BLine0331,ocys);fprintf(ocys,"\n");
			}

			for (I=0;I<BladeCntP;I++)//face set
			{
				fputs(BLineSet0,ocys);
				fputs(BladeI[I].myChar,ocys);fprintf(ocys,"\n");

				fputs(BLineSet1,ocys);
				fprintf(ocys,"%5.2f",Xib[I]);fputs(BLineSet11,ocys);
				fprintf(ocys,"%5.2f",Yib[I]);fputs(BLineSet12,ocys);
				fprintf(ocys,"%5.2f",Zib[I]);fputs(BLineSet13,ocys);
				fprintf(ocys,"\n");
				fputs(BLineSet2,ocys);
				fprintf(ocys,"%5.2f",Xit[I]);fputs(BLineSet21,ocys);
				fprintf(ocys,"%5.2f",Yit[I]);fputs(BLineSet22,ocys);
				fprintf(ocys,"%5.2f",Zit[I]);fputs(BLineSet23,ocys);
				fprintf(ocys,"%5.2f",Ri[I]);fputs(BLineSet24,ocys);
				fprintf(ocys,"\n");
				fputs(BLineSet3,ocys);
				fputs(BladeI[I].myChar,ocys);
				fputs(BLineSet31,ocys);fprintf(ocys,"\n");
				fputs(BLineSet0,ocys);
				fputs(BladeO[I].myChar,ocys);fprintf(ocys,"\n");
				fputs(BLineSet1,ocys);
				fprintf(ocys,"%5.2f",Xob[I]);fputs(BLineSet11,ocys);
				fprintf(ocys,"%5.2f",Yob[I]);fputs(BLineSet12,ocys);
				fprintf(ocys,"%5.2f",Zob[I]);fputs(BLineSet13,ocys);
				fprintf(ocys,"\n");
				fputs(BLineSet2,ocys);
				fprintf(ocys,"%5.2f",Xot[I]);fputs(BLineSet21,ocys);
				fprintf(ocys,"%5.2f",Yot[I]);fputs(BLineSet22,ocys);
				fprintf(ocys,"%5.2f",Zot[I]);fputs(BLineSet23,ocys);
				fprintf(ocys,"%5.2f",Ro[I]);fputs(BLineSet24,ocys);
				fprintf(ocys,"\n");
				fputs(BLineSet3,ocys);
				fputs(BladeO[I].myChar,ocys);
				fputs(BLineSet31,ocys);fprintf(ocys,"\n");
			}
//core set
				fputs(BLine007,ocys);fprintf(ocys,"\n");
				fputs(BLine008,ocys);
				fprintf(ocys,"%4.2f",bottom2);
				fputs(BLine0081,ocys);fprintf(ocys,"\n");
				fputs(BLine009,ocys);
				fprintf(ocys,"%4.2f",top1);
				fputs(BLine0091,ocys);
				fprintf(ocys,"%4.2f",bodyDia2/2.0);
				fputs(BLine0092,ocys);fprintf(ocys,"\n");
				fputs(BLine010,ocys);fprintf(ocys,"\n");
				for (I=0;I<BladeCntP;I++)//surfaces
				{
					fputs(BLine011,ocys);fputs(Blade[I].myChar,ocys);fprintf(ocys,"\n");
					fputs(BLine012,ocys);
					fputs(Blade[I].myChar,ocys);
					fputs(BLine0121,ocys);fprintf(ocys,"\n");
					fputs(BLine013,ocys);
					fputs(BladeO[I].myChar,ocys);
					fputs(BLine0131,ocys);fprintf(ocys,"\n");
				}
//delete BladeI face
/*				fputs(BLine001,ocys);fprintf(ocys,"\n");
				for (I=0;I<BladeCntP;I++)//surfaces
				{
					fputs(BLine0010,ocys);
					fputs(BladeI[I].myChar,ocys);
					fputs(BLine0011,ocys);fprintf(ocys,"\n");
				}*/
//delete BladeO face
				fputs(BLine001,ocys);fprintf(ocys,"\n");
				for (I=0;I<BladeCntP;I++)//surfaces
				{
					fputs(BLine0010,ocys);
					fputs(BladeO[I].myChar,ocys);
					fputs(BLine0011,ocys);fprintf(ocys,"\n");
				}
//rename face Blade to BladeO
				fputs(BLine003,ocys);fprintf(ocys,"\n");
				for (I=0;I<BladeCntP;I++)//surfaces
				{
					fputs(BLine0030,ocys);
					fputs(Blade[I].myChar,ocys);
					fputs(BLine0031,ocys);fprintf(ocys,"\n");
					fputs(BLine0040,ocys);
					fputs(BladeO[I].myChar,ocys);
					fputs(BLine0041,ocys);fprintf(ocys,"\n");
				}
//delete BladeI faceset
				fputs(BLine002,ocys);fprintf(ocys,"\n");
				for (I=0;I<BladeCntP;I++)//surfaces
				{
					fputs(BLine0020,ocys);
					fputs(BladeI[I].myChar,ocys);
					fputs(BLine0021,ocys);fprintf(ocys,"\n");
				}
//delete BladeO faceset
				fputs(BLine002,ocys);fprintf(ocys,"\n");
				for (I=0;I<BladeCntP;I++)//surfaces
				{
					fputs(BLine0020,ocys);
					fputs(BladeO[I].myChar,ocys);
					fputs(BLine0021,ocys);fprintf(ocys,"\n");
				}

			fclose(ocys);
		return 0;
	} //end WriteBladeFaceByCylinderNew//******
//new index


//******************
	int AssignIndexIJ(myString indexIJ[18][30])
	{

		strcpy(indexIJ[0][0].myChar, "1-1");
		strcpy(indexIJ[0][1].myChar, "1-2");
		strcpy(indexIJ[0][2].myChar, "1-3");
		strcpy(indexIJ[0][3].myChar, "1-4");
		strcpy(indexIJ[0][4].myChar, "1-5");
		strcpy(indexIJ[0][5].myChar, "1-6");
		strcpy(indexIJ[0][6].myChar, "1-7");
		strcpy(indexIJ[0][7].myChar, "1-8");
		strcpy(indexIJ[0][8].myChar, "1-9");
		strcpy(indexIJ[0][9].myChar, "1-10");
		strcpy(indexIJ[0][10].myChar, "1-11");
		strcpy(indexIJ[0][11].myChar, "1-12");
		strcpy(indexIJ[0][12].myChar, "1-13");
		strcpy(indexIJ[0][13].myChar, "1-14");
		strcpy(indexIJ[0][14].myChar, "1-15");
		strcpy(indexIJ[0][15].myChar, "1-16");
		strcpy(indexIJ[0][16].myChar, "1-17");
		strcpy(indexIJ[0][17].myChar, "1-18");
		strcpy(indexIJ[0][18].myChar, "1-19");
		strcpy(indexIJ[0][19].myChar, "1-20");
		strcpy(indexIJ[0][20].myChar, "1-21");
		strcpy(indexIJ[0][21].myChar, "1-22");
		strcpy(indexIJ[0][22].myChar, "1-23");
		strcpy(indexIJ[0][23].myChar, "1-24");
		strcpy(indexIJ[0][24].myChar, "1-25");
		strcpy(indexIJ[0][25].myChar, "1-26");
		strcpy(indexIJ[0][26].myChar, "1-27");
		strcpy(indexIJ[0][27].myChar, "1-28");
		strcpy(indexIJ[0][28].myChar, "1-29");
		strcpy(indexIJ[0][29].myChar, "1-30");

		strcpy(indexIJ[1][0].myChar, "2-1");
		strcpy(indexIJ[1][1].myChar, "2-2");
		strcpy(indexIJ[1][2].myChar, "2-3");
		strcpy(indexIJ[1][3].myChar, "2-4");
		strcpy(indexIJ[1][4].myChar, "2-5");
		strcpy(indexIJ[1][5].myChar, "2-6");
		strcpy(indexIJ[1][6].myChar, "2-7");
		strcpy(indexIJ[1][7].myChar, "2-8");
		strcpy(indexIJ[1][8].myChar, "2-9");
		strcpy(indexIJ[1][9].myChar, "2-10");
		strcpy(indexIJ[1][10].myChar, "2-11");
		strcpy(indexIJ[1][11].myChar, "2-12");
		strcpy(indexIJ[1][12].myChar, "2-13");
		strcpy(indexIJ[1][13].myChar, "2-14");
		strcpy(indexIJ[1][14].myChar, "2-15");
		strcpy(indexIJ[1][15].myChar, "2-16");
		strcpy(indexIJ[1][16].myChar, "2-17");
		strcpy(indexIJ[1][17].myChar, "2-18");
		strcpy(indexIJ[1][18].myChar, "2-19");
		strcpy(indexIJ[1][19].myChar, "2-20");
		strcpy(indexIJ[1][20].myChar, "2-21");
		strcpy(indexIJ[1][21].myChar, "2-22");
		strcpy(indexIJ[1][22].myChar, "2-23");
		strcpy(indexIJ[1][23].myChar, "2-24");
		strcpy(indexIJ[1][24].myChar, "2-25");
		strcpy(indexIJ[1][25].myChar, "2-26");
		strcpy(indexIJ[1][26].myChar, "2-27");
		strcpy(indexIJ[1][27].myChar, "2-28");
		strcpy(indexIJ[1][28].myChar, "2-29");
		strcpy(indexIJ[1][29].myChar, "2-30");

		strcpy(indexIJ[2][0].myChar, "3-1");
		strcpy(indexIJ[2][1].myChar, "3-2");
		strcpy(indexIJ[2][2].myChar, "3-3");
		strcpy(indexIJ[2][3].myChar, "3-4");
		strcpy(indexIJ[2][4].myChar, "3-5");
		strcpy(indexIJ[2][5].myChar, "3-6");
		strcpy(indexIJ[2][6].myChar, "3-7");
		strcpy(indexIJ[2][7].myChar, "3-8");
		strcpy(indexIJ[2][8].myChar, "3-9");
		strcpy(indexIJ[2][9].myChar, "3-10");
		strcpy(indexIJ[2][10].myChar, "3-11");
		strcpy(indexIJ[2][11].myChar, "3-12");
		strcpy(indexIJ[2][12].myChar, "3-13");
		strcpy(indexIJ[2][13].myChar, "3-14");
		strcpy(indexIJ[2][14].myChar, "3-15");
		strcpy(indexIJ[2][15].myChar, "3-16");
		strcpy(indexIJ[2][16].myChar, "3-17");
		strcpy(indexIJ[2][17].myChar, "3-18");
		strcpy(indexIJ[2][18].myChar, "3-19");
		strcpy(indexIJ[2][19].myChar, "3-20");
		strcpy(indexIJ[2][20].myChar, "3-21");
		strcpy(indexIJ[2][21].myChar, "3-22");
		strcpy(indexIJ[2][22].myChar, "3-23");
		strcpy(indexIJ[2][23].myChar, "3-24");
		strcpy(indexIJ[2][24].myChar, "3-25");
		strcpy(indexIJ[2][25].myChar, "3-26");
		strcpy(indexIJ[2][26].myChar, "3-27");
		strcpy(indexIJ[2][27].myChar, "3-28");
		strcpy(indexIJ[2][28].myChar, "3-29");
		strcpy(indexIJ[2][29].myChar, "3-30");


		strcpy(indexIJ[3][0].myChar, "4-1");
		strcpy(indexIJ[3][1].myChar, "4-2");
		strcpy(indexIJ[3][2].myChar, "4-3");
		strcpy(indexIJ[3][3].myChar, "4-4");
		strcpy(indexIJ[3][4].myChar, "4-5");
		strcpy(indexIJ[3][5].myChar, "4-6");
		strcpy(indexIJ[3][6].myChar, "4-7");
		strcpy(indexIJ[3][7].myChar, "4-8");
		strcpy(indexIJ[3][8].myChar, "4-9");
		strcpy(indexIJ[3][9].myChar, "4-10");
		strcpy(indexIJ[3][10].myChar, "4-11");
		strcpy(indexIJ[3][11].myChar, "4-12");
		strcpy(indexIJ[3][12].myChar, "4-13");
		strcpy(indexIJ[3][13].myChar, "4-14");
		strcpy(indexIJ[3][14].myChar, "4-15");
		strcpy(indexIJ[3][15].myChar, "4-16");
		strcpy(indexIJ[3][16].myChar, "4-17");
		strcpy(indexIJ[3][17].myChar, "4-18");
		strcpy(indexIJ[3][18].myChar, "4-19");
		strcpy(indexIJ[3][19].myChar, "4-20");
		strcpy(indexIJ[3][20].myChar, "4-21");
		strcpy(indexIJ[3][21].myChar, "4-22");
		strcpy(indexIJ[3][22].myChar, "4-23");
		strcpy(indexIJ[3][23].myChar, "4-24");
		strcpy(indexIJ[3][24].myChar, "4-25");
		strcpy(indexIJ[3][25].myChar, "4-26");
		strcpy(indexIJ[3][26].myChar, "4-27");
		strcpy(indexIJ[3][27].myChar, "4-28");
		strcpy(indexIJ[3][28].myChar, "4-29");
		strcpy(indexIJ[3][29].myChar, "4-30");


		strcpy(indexIJ[4][0].myChar, "5-1");
		strcpy(indexIJ[4][1].myChar, "5-2");
		strcpy(indexIJ[4][2].myChar, "5-3");
		strcpy(indexIJ[4][3].myChar, "5-4");
		strcpy(indexIJ[4][4].myChar, "5-5");
		strcpy(indexIJ[4][5].myChar, "5-6");
		strcpy(indexIJ[4][6].myChar, "5-7");
		strcpy(indexIJ[4][7].myChar, "5-8");
		strcpy(indexIJ[4][8].myChar, "5-9");
		strcpy(indexIJ[4][9].myChar, "5-10");
		strcpy(indexIJ[4][10].myChar, "5-11");
		strcpy(indexIJ[4][11].myChar, "5-12");
		strcpy(indexIJ[4][12].myChar, "5-13");
		strcpy(indexIJ[4][13].myChar, "5-14");
		strcpy(indexIJ[4][14].myChar, "5-15");
		strcpy(indexIJ[4][15].myChar, "5-16");
		strcpy(indexIJ[4][16].myChar, "5-17");
		strcpy(indexIJ[4][17].myChar, "5-18");
		strcpy(indexIJ[4][18].myChar, "5-19");
		strcpy(indexIJ[4][19].myChar, "5-20");
		strcpy(indexIJ[4][20].myChar, "5-21");
		strcpy(indexIJ[4][21].myChar, "5-22");
		strcpy(indexIJ[4][22].myChar, "5-23");
		strcpy(indexIJ[4][23].myChar, "5-24");
		strcpy(indexIJ[4][24].myChar, "5-25");
		strcpy(indexIJ[4][25].myChar, "5-26");
		strcpy(indexIJ[4][26].myChar, "5-27");
		strcpy(indexIJ[4][27].myChar, "5-28");
		strcpy(indexIJ[4][28].myChar, "5-29");
		strcpy(indexIJ[4][29].myChar, "5-30");


		strcpy(indexIJ[5][0].myChar, "6-1");
		strcpy(indexIJ[5][1].myChar, "6-2");
		strcpy(indexIJ[5][2].myChar, "6-3");
		strcpy(indexIJ[5][3].myChar, "6-4");
		strcpy(indexIJ[5][4].myChar, "6-5");
		strcpy(indexIJ[5][5].myChar, "6-6");
		strcpy(indexIJ[5][6].myChar, "6-7");
		strcpy(indexIJ[5][7].myChar, "6-8");
		strcpy(indexIJ[5][8].myChar, "6-9");
		strcpy(indexIJ[5][9].myChar, "6-10");
		strcpy(indexIJ[5][10].myChar, "6-11");
		strcpy(indexIJ[5][11].myChar, "6-12");
		strcpy(indexIJ[5][12].myChar, "6-13");
		strcpy(indexIJ[5][13].myChar, "6-14");
		strcpy(indexIJ[5][14].myChar, "6-15");
		strcpy(indexIJ[5][15].myChar, "6-16");
		strcpy(indexIJ[5][16].myChar, "6-17");
		strcpy(indexIJ[5][17].myChar, "6-18");
		strcpy(indexIJ[5][18].myChar, "6-19");
		strcpy(indexIJ[5][19].myChar, "6-20");
		strcpy(indexIJ[5][20].myChar, "6-21");
		strcpy(indexIJ[5][21].myChar, "6-22");
		strcpy(indexIJ[5][22].myChar, "6-23");
		strcpy(indexIJ[5][23].myChar, "6-24");
		strcpy(indexIJ[5][24].myChar, "6-25");
		strcpy(indexIJ[5][25].myChar, "6-26");
		strcpy(indexIJ[5][26].myChar, "6-27");
		strcpy(indexIJ[5][27].myChar, "6-28");
		strcpy(indexIJ[5][28].myChar, "6-29");
		strcpy(indexIJ[5][29].myChar, "6-30");


		strcpy(indexIJ[6][0].myChar, "7-1");
		strcpy(indexIJ[6][1].myChar, "7-2");
		strcpy(indexIJ[6][2].myChar, "7-3");
		strcpy(indexIJ[6][3].myChar, "7-4");
		strcpy(indexIJ[6][4].myChar, "7-5");
		strcpy(indexIJ[6][5].myChar, "7-6");
		strcpy(indexIJ[6][6].myChar, "7-7");
		strcpy(indexIJ[6][7].myChar, "7-8");
		strcpy(indexIJ[6][8].myChar, "7-9");
		strcpy(indexIJ[6][9].myChar, "7-10");
		strcpy(indexIJ[6][10].myChar, "7-11");
		strcpy(indexIJ[6][11].myChar, "7-12");
		strcpy(indexIJ[6][12].myChar, "7-13");
		strcpy(indexIJ[6][13].myChar, "7-14");
		strcpy(indexIJ[6][14].myChar, "7-15");
		strcpy(indexIJ[6][15].myChar, "7-16");
		strcpy(indexIJ[6][16].myChar, "7-17");
		strcpy(indexIJ[6][17].myChar, "7-18");
		strcpy(indexIJ[6][18].myChar, "7-19");
		strcpy(indexIJ[6][19].myChar, "7-20");
		strcpy(indexIJ[6][20].myChar, "7-21");
		strcpy(indexIJ[6][21].myChar, "7-22");
		strcpy(indexIJ[6][22].myChar, "7-23");
		strcpy(indexIJ[6][23].myChar, "7-24");
		strcpy(indexIJ[6][24].myChar, "7-25");
		strcpy(indexIJ[6][25].myChar, "7-26");
		strcpy(indexIJ[6][26].myChar, "7-27");
		strcpy(indexIJ[6][27].myChar, "7-28");
		strcpy(indexIJ[6][28].myChar, "7-29");
		strcpy(indexIJ[6][29].myChar, "7-30");


		strcpy(indexIJ[7][0].myChar, "8-1");
		strcpy(indexIJ[7][1].myChar, "8-2");
		strcpy(indexIJ[7][2].myChar, "8-3");
		strcpy(indexIJ[7][3].myChar, "8-4");
		strcpy(indexIJ[7][4].myChar, "8-5");
		strcpy(indexIJ[7][5].myChar, "8-6");
		strcpy(indexIJ[7][6].myChar, "8-7");
		strcpy(indexIJ[7][7].myChar, "8-8");
		strcpy(indexIJ[7][8].myChar, "8-9");
		strcpy(indexIJ[7][9].myChar, "8-10");
		strcpy(indexIJ[7][10].myChar, "8-11");
		strcpy(indexIJ[7][11].myChar, "8-12");
		strcpy(indexIJ[7][12].myChar, "8-13");
		strcpy(indexIJ[7][13].myChar, "8-14");
		strcpy(indexIJ[7][14].myChar, "8-15");
		strcpy(indexIJ[7][15].myChar, "8-16");
		strcpy(indexIJ[7][16].myChar, "8-17");
		strcpy(indexIJ[7][17].myChar, "8-18");
		strcpy(indexIJ[7][18].myChar, "8-19");
		strcpy(indexIJ[7][19].myChar, "8-20");
		strcpy(indexIJ[7][20].myChar, "8-21");
		strcpy(indexIJ[7][21].myChar, "8-22");
		strcpy(indexIJ[7][22].myChar, "8-23");
		strcpy(indexIJ[7][23].myChar, "8-24");
		strcpy(indexIJ[7][24].myChar, "8-25");
		strcpy(indexIJ[7][25].myChar, "8-26");
		strcpy(indexIJ[7][26].myChar, "8-27");
		strcpy(indexIJ[7][27].myChar, "8-28");
		strcpy(indexIJ[7][28].myChar, "8-29");
		strcpy(indexIJ[7][29].myChar, "8-30");

		strcpy(indexIJ[8][0].myChar, "9-1");
		strcpy(indexIJ[8][1].myChar, "9-2");
		strcpy(indexIJ[8][2].myChar, "9-3");
		strcpy(indexIJ[8][3].myChar, "9-4");
		strcpy(indexIJ[8][4].myChar, "9-5");
		strcpy(indexIJ[8][5].myChar, "9-6");
		strcpy(indexIJ[8][6].myChar, "9-7");
		strcpy(indexIJ[8][7].myChar, "9-8");
		strcpy(indexIJ[8][8].myChar, "9-9");
		strcpy(indexIJ[8][9].myChar, "9-10");
		strcpy(indexIJ[8][10].myChar, "9-11");
		strcpy(indexIJ[8][11].myChar, "9-12");
		strcpy(indexIJ[8][12].myChar, "9-13");
		strcpy(indexIJ[8][13].myChar, "9-14");
		strcpy(indexIJ[8][14].myChar, "9-15");
		strcpy(indexIJ[8][15].myChar, "9-16");
		strcpy(indexIJ[8][16].myChar, "9-17");
		strcpy(indexIJ[8][17].myChar, "9-18");
		strcpy(indexIJ[8][18].myChar, "9-19");
		strcpy(indexIJ[8][19].myChar, "9-20");
		strcpy(indexIJ[8][20].myChar, "9-21");
		strcpy(indexIJ[8][21].myChar, "9-22");
		strcpy(indexIJ[8][22].myChar, "9-23");
		strcpy(indexIJ[8][23].myChar, "9-24");
		strcpy(indexIJ[8][24].myChar, "9-25");
		strcpy(indexIJ[8][25].myChar, "9-26");
		strcpy(indexIJ[8][26].myChar, "9-27");
		strcpy(indexIJ[8][27].myChar, "9-28");
		strcpy(indexIJ[8][28].myChar, "9-29");
		strcpy(indexIJ[8][29].myChar, "9-30");


		strcpy(indexIJ[9][0].myChar, "10-1");
		strcpy(indexIJ[9][1].myChar, "10-2");
		strcpy(indexIJ[9][2].myChar, "10-3");
		strcpy(indexIJ[9][3].myChar, "10-4");
		strcpy(indexIJ[9][4].myChar, "10-5");
		strcpy(indexIJ[9][5].myChar, "10-6");
		strcpy(indexIJ[9][6].myChar, "10-7");
		strcpy(indexIJ[9][7].myChar, "10-8");
		strcpy(indexIJ[9][8].myChar, "10-9");
		strcpy(indexIJ[9][9].myChar, "10-10");
		strcpy(indexIJ[9][10].myChar, "10-11");
		strcpy(indexIJ[9][11].myChar, "10-12");
		strcpy(indexIJ[9][12].myChar, "10-13");
		strcpy(indexIJ[9][13].myChar, "10-14");
		strcpy(indexIJ[9][14].myChar, "10-15");
		strcpy(indexIJ[9][15].myChar, "10-16");
		strcpy(indexIJ[9][16].myChar, "10-17");
		strcpy(indexIJ[9][17].myChar, "10-18");
		strcpy(indexIJ[9][18].myChar, "10-19");
		strcpy(indexIJ[9][19].myChar, "10-20");

		strcpy(indexIJ[10][0].myChar, "11-1");
		strcpy(indexIJ[10][1].myChar, "11-2");
		strcpy(indexIJ[10][2].myChar, "11-3");
		strcpy(indexIJ[10][3].myChar, "11-4");
		strcpy(indexIJ[10][4].myChar, "11-5");
		strcpy(indexIJ[10][5].myChar, "11-6");
		strcpy(indexIJ[10][6].myChar, "11-7");
		strcpy(indexIJ[10][7].myChar, "11-8");
		strcpy(indexIJ[10][8].myChar, "11-9");
		strcpy(indexIJ[10][9].myChar, "11-10");
		strcpy(indexIJ[10][10].myChar, "11-11");
		strcpy(indexIJ[10][11].myChar, "11-12");
		strcpy(indexIJ[10][12].myChar, "11-13");
		strcpy(indexIJ[10][13].myChar, "11-14");
		strcpy(indexIJ[10][14].myChar, "11-15");
		strcpy(indexIJ[10][15].myChar, "11-16");
		strcpy(indexIJ[10][16].myChar, "11-17");
		strcpy(indexIJ[10][17].myChar, "11-18");
		strcpy(indexIJ[10][18].myChar, "11-19");
		strcpy(indexIJ[10][19].myChar, "11-20");

		strcpy(indexIJ[11][0].myChar, "12-1");
		strcpy(indexIJ[11][1].myChar, "12-2");
		strcpy(indexIJ[11][2].myChar, "12-3");
		strcpy(indexIJ[11][3].myChar, "12-4");
		strcpy(indexIJ[11][4].myChar, "12-5");
		strcpy(indexIJ[11][5].myChar, "12-6");
		strcpy(indexIJ[11][6].myChar, "12-7");
		strcpy(indexIJ[11][7].myChar, "12-8");
		strcpy(indexIJ[11][8].myChar, "12-9");
		strcpy(indexIJ[11][9].myChar, "12-10");
		strcpy(indexIJ[11][10].myChar, "12-11");
		strcpy(indexIJ[11][11].myChar, "12-12");
		strcpy(indexIJ[11][12].myChar, "12-13");
		strcpy(indexIJ[11][13].myChar, "12-14");
		strcpy(indexIJ[11][14].myChar, "12-15");
		strcpy(indexIJ[11][15].myChar, "12-16");
		strcpy(indexIJ[11][16].myChar, "12-17");
		strcpy(indexIJ[11][17].myChar, "12-18");
		strcpy(indexIJ[11][18].myChar, "12-19");
		strcpy(indexIJ[11][19].myChar, "12-20");

		strcpy(indexIJ[12][0].myChar, "13-1");
		strcpy(indexIJ[12][1].myChar, "13-2");
		strcpy(indexIJ[12][2].myChar, "13-3");
		strcpy(indexIJ[12][3].myChar, "13-4");
		strcpy(indexIJ[12][4].myChar, "13-5");
		strcpy(indexIJ[12][5].myChar, "13-6");
		strcpy(indexIJ[12][6].myChar, "13-7");
		strcpy(indexIJ[12][7].myChar, "13-8");
		strcpy(indexIJ[12][8].myChar, "13-9");
		strcpy(indexIJ[12][9].myChar, "13-10");
		strcpy(indexIJ[12][10].myChar, "13-11");
		strcpy(indexIJ[12][11].myChar, "13-12");
		strcpy(indexIJ[12][12].myChar, "13-13");
		strcpy(indexIJ[12][13].myChar, "13-14");
		strcpy(indexIJ[12][14].myChar, "13-15");
		strcpy(indexIJ[12][15].myChar, "13-16");
		strcpy(indexIJ[12][16].myChar, "13-17");
		strcpy(indexIJ[12][17].myChar, "13-18");
		strcpy(indexIJ[12][18].myChar, "13-19");
		strcpy(indexIJ[12][19].myChar, "13-20");

		strcpy(indexIJ[13][0].myChar, "14-1");
		strcpy(indexIJ[13][1].myChar, "14-2");
		strcpy(indexIJ[13][2].myChar, "14-3");
		strcpy(indexIJ[13][3].myChar, "14-4");
		strcpy(indexIJ[13][4].myChar, "14-5");
		strcpy(indexIJ[13][5].myChar, "14-6");
		strcpy(indexIJ[13][6].myChar, "14-7");
		strcpy(indexIJ[13][7].myChar, "14-8");
		strcpy(indexIJ[13][8].myChar, "14-9");
		strcpy(indexIJ[13][9].myChar, "14-10");
		strcpy(indexIJ[13][10].myChar, "14-11");
		strcpy(indexIJ[13][11].myChar, "14-12");
		strcpy(indexIJ[13][12].myChar, "14-13");
		strcpy(indexIJ[13][13].myChar, "14-14");
		strcpy(indexIJ[13][14].myChar, "14-15");
		strcpy(indexIJ[13][15].myChar, "14-16");
		strcpy(indexIJ[13][16].myChar, "14-17");
		strcpy(indexIJ[13][17].myChar, "14-18");
		strcpy(indexIJ[13][18].myChar, "14-19");
		strcpy(indexIJ[13][19].myChar, "14-20");

		strcpy(indexIJ[14][0].myChar, "15-1");
		strcpy(indexIJ[14][1].myChar, "15-2");
		strcpy(indexIJ[14][2].myChar, "15-3");
		strcpy(indexIJ[14][3].myChar, "15-4");
		strcpy(indexIJ[14][4].myChar, "15-5");
		strcpy(indexIJ[14][5].myChar, "15-6");
		strcpy(indexIJ[14][6].myChar, "15-7");
		strcpy(indexIJ[14][7].myChar, "15-8");
		strcpy(indexIJ[14][8].myChar, "15-9");
		strcpy(indexIJ[14][9].myChar, "15-10");
		strcpy(indexIJ[14][10].myChar, "15-11");
		strcpy(indexIJ[14][11].myChar, "15-12");
		strcpy(indexIJ[14][12].myChar, "15-13");
		strcpy(indexIJ[14][13].myChar, "15-14");
		strcpy(indexIJ[14][14].myChar, "15-15");
		strcpy(indexIJ[14][15].myChar, "15-16");
		strcpy(indexIJ[14][16].myChar, "15-17");
		strcpy(indexIJ[14][17].myChar, "15-18");
		strcpy(indexIJ[14][18].myChar, "15-19");
		strcpy(indexIJ[14][19].myChar, "15-20");

		strcpy(indexIJ[15][0].myChar, "16-1");
		strcpy(indexIJ[15][1].myChar, "16-2");
		strcpy(indexIJ[15][2].myChar, "16-3");
		strcpy(indexIJ[15][3].myChar, "16-4");
		strcpy(indexIJ[15][4].myChar, "16-5");
		strcpy(indexIJ[15][5].myChar, "16-6");
		strcpy(indexIJ[15][6].myChar, "16-7");
		strcpy(indexIJ[15][7].myChar, "16-8");
		strcpy(indexIJ[15][8].myChar, "16-9");
		strcpy(indexIJ[15][9].myChar, "16-10");
		strcpy(indexIJ[15][10].myChar, "16-11");
		strcpy(indexIJ[15][11].myChar, "16-12");
		strcpy(indexIJ[15][12].myChar, "16-13");
		strcpy(indexIJ[15][13].myChar, "16-14");
		strcpy(indexIJ[15][14].myChar, "16-15");
		strcpy(indexIJ[15][15].myChar, "16-16");
		strcpy(indexIJ[15][16].myChar, "16-17");
		strcpy(indexIJ[15][17].myChar, "16-18");
		strcpy(indexIJ[15][18].myChar, "16-19");
		strcpy(indexIJ[15][19].myChar, "16-20");

		strcpy(indexIJ[16][0].myChar, "17-1");
		strcpy(indexIJ[16][1].myChar, "17-2");
		strcpy(indexIJ[16][2].myChar, "17-3");
		strcpy(indexIJ[16][3].myChar, "17-4");
		strcpy(indexIJ[16][4].myChar, "17-5");
		strcpy(indexIJ[16][5].myChar, "17-6");
		strcpy(indexIJ[16][6].myChar, "17-7");
		strcpy(indexIJ[16][7].myChar, "17-8");
		strcpy(indexIJ[16][8].myChar, "17-9");
		strcpy(indexIJ[16][9].myChar, "17-10");
		strcpy(indexIJ[16][10].myChar, "17-11");
		strcpy(indexIJ[16][11].myChar, "17-12");
		strcpy(indexIJ[16][12].myChar, "17-13");
		strcpy(indexIJ[16][13].myChar, "17-14");
		strcpy(indexIJ[16][14].myChar, "17-15");
		strcpy(indexIJ[16][15].myChar, "17-16");
		strcpy(indexIJ[16][16].myChar, "17-17");
		strcpy(indexIJ[16][17].myChar, "17-18");
		strcpy(indexIJ[16][18].myChar, "17-19");
		strcpy(indexIJ[16][19].myChar, "17-20");

		strcpy(indexIJ[17][0].myChar, "18-1");
		strcpy(indexIJ[17][1].myChar, "18-2");
		strcpy(indexIJ[17][2].myChar, "18-3");
		strcpy(indexIJ[17][3].myChar, "18-4");
		strcpy(indexIJ[17][4].myChar, "18-5");
		strcpy(indexIJ[17][5].myChar, "18-6");
		strcpy(indexIJ[17][6].myChar, "18-7");
		strcpy(indexIJ[17][7].myChar, "18-8");
		strcpy(indexIJ[17][8].myChar, "18-9");
		strcpy(indexIJ[17][9].myChar, "18-10");
		strcpy(indexIJ[17][10].myChar, "18-11");
		strcpy(indexIJ[17][11].myChar, "18-12");
		strcpy(indexIJ[17][12].myChar, "18-13");
		strcpy(indexIJ[17][13].myChar, "18-14");
		strcpy(indexIJ[17][14].myChar, "18-15");
		strcpy(indexIJ[17][15].myChar, "18-16");
		strcpy(indexIJ[17][16].myChar, "18-17");
		strcpy(indexIJ[17][17].myChar, "18-18");
		strcpy(indexIJ[17][18].myChar, "18-19");
		strcpy(indexIJ[17][19].myChar, "18-20");
		return 0;
	} //end assign indexIJ

	int AssignIndexI_J(myString indexI_J[18][30])
	{

		strcpy(indexI_J[0][0].myChar, "1_1");
		strcpy(indexI_J[0][1].myChar, "1_2");
		strcpy(indexI_J[0][2].myChar, "1_3");
		strcpy(indexI_J[0][3].myChar, "1_4");
		strcpy(indexI_J[0][4].myChar, "1_5");
		strcpy(indexI_J[0][5].myChar, "1_6");
		strcpy(indexI_J[0][6].myChar, "1_7");
		strcpy(indexI_J[0][7].myChar, "1_8");
		strcpy(indexI_J[0][8].myChar, "1_9");
		strcpy(indexI_J[0][9].myChar, "1_10");
		strcpy(indexI_J[0][10].myChar, "1_11");
		strcpy(indexI_J[0][11].myChar, "1_12");
		strcpy(indexI_J[0][12].myChar, "1_13");
		strcpy(indexI_J[0][13].myChar, "1_14");
		strcpy(indexI_J[0][14].myChar, "1_15");
		strcpy(indexI_J[0][15].myChar, "1_16");
		strcpy(indexI_J[0][16].myChar, "1_17");
		strcpy(indexI_J[0][17].myChar, "1_18");
		strcpy(indexI_J[0][18].myChar, "1_19");
		strcpy(indexI_J[0][19].myChar, "1_20");
		strcpy(indexI_J[0][20].myChar, "1_21");
		strcpy(indexI_J[0][21].myChar, "1_22");
		strcpy(indexI_J[0][22].myChar, "1_23");
		strcpy(indexI_J[0][23].myChar, "1_24");
		strcpy(indexI_J[0][24].myChar, "1_25");
		strcpy(indexI_J[0][25].myChar, "1_26");
		strcpy(indexI_J[0][26].myChar, "1_27");
		strcpy(indexI_J[0][27].myChar, "1_28");
		strcpy(indexI_J[0][28].myChar, "1_29");
		strcpy(indexI_J[0][29].myChar, "1_30");

		strcpy(indexI_J[1][0].myChar, "2_1");
		strcpy(indexI_J[1][1].myChar, "2_2");
		strcpy(indexI_J[1][2].myChar, "2_3");
		strcpy(indexI_J[1][3].myChar, "2_4");
		strcpy(indexI_J[1][4].myChar, "2_5");
		strcpy(indexI_J[1][5].myChar, "2_6");
		strcpy(indexI_J[1][6].myChar, "2_7");
		strcpy(indexI_J[1][7].myChar, "2_8");
		strcpy(indexI_J[1][8].myChar, "2_9");
		strcpy(indexI_J[1][9].myChar, "2_10");
		strcpy(indexI_J[1][10].myChar, "2_11");
		strcpy(indexI_J[1][11].myChar, "2_12");
		strcpy(indexI_J[1][12].myChar, "2_13");
		strcpy(indexI_J[1][13].myChar, "2_14");
		strcpy(indexI_J[1][14].myChar, "2_15");
		strcpy(indexI_J[1][15].myChar, "2_16");
		strcpy(indexI_J[1][16].myChar, "2_17");
		strcpy(indexI_J[1][17].myChar, "2_18");
		strcpy(indexI_J[1][18].myChar, "2_19");
		strcpy(indexI_J[1][19].myChar, "2_20");
		strcpy(indexI_J[1][20].myChar, "2_21");
		strcpy(indexI_J[1][21].myChar, "2_22");
		strcpy(indexI_J[1][22].myChar, "2_23");
		strcpy(indexI_J[1][23].myChar, "2_24");
		strcpy(indexI_J[1][24].myChar, "2_25");
		strcpy(indexI_J[1][25].myChar, "2_26");
		strcpy(indexI_J[1][26].myChar, "2_27");
		strcpy(indexI_J[1][27].myChar, "2_28");
		strcpy(indexI_J[1][28].myChar, "2_29");
		strcpy(indexI_J[1][29].myChar, "2_30");

		strcpy(indexI_J[2][0].myChar, "3_1");
		strcpy(indexI_J[2][1].myChar, "3_2");
		strcpy(indexI_J[2][2].myChar, "3_3");
		strcpy(indexI_J[2][3].myChar, "3_4");
		strcpy(indexI_J[2][4].myChar, "3_5");
		strcpy(indexI_J[2][5].myChar, "3_6");
		strcpy(indexI_J[2][6].myChar, "3_7");
		strcpy(indexI_J[2][7].myChar, "3_8");
		strcpy(indexI_J[2][8].myChar, "3_9");
		strcpy(indexI_J[2][9].myChar, "3_10");
		strcpy(indexI_J[2][10].myChar, "3_11");
		strcpy(indexI_J[2][11].myChar, "3_12");
		strcpy(indexI_J[2][12].myChar, "3_13");
		strcpy(indexI_J[2][13].myChar, "3_14");
		strcpy(indexI_J[2][14].myChar, "3_15");
		strcpy(indexI_J[2][15].myChar, "3_16");
		strcpy(indexI_J[2][16].myChar, "3_17");
		strcpy(indexI_J[2][17].myChar, "3_18");
		strcpy(indexI_J[2][18].myChar, "3_19");
		strcpy(indexI_J[2][19].myChar, "3_20");
		strcpy(indexI_J[2][20].myChar, "3_21");
		strcpy(indexI_J[2][21].myChar, "3_22");
		strcpy(indexI_J[2][22].myChar, "3_23");
		strcpy(indexI_J[2][23].myChar, "3_24");
		strcpy(indexI_J[2][24].myChar, "3_25");
		strcpy(indexI_J[2][25].myChar, "3_26");
		strcpy(indexI_J[2][26].myChar, "3_27");
		strcpy(indexI_J[2][27].myChar, "3_28");
		strcpy(indexI_J[2][28].myChar, "3_29");
		strcpy(indexI_J[2][29].myChar, "3_30");


		strcpy(indexI_J[3][0].myChar, "4_1");
		strcpy(indexI_J[3][1].myChar, "4_2");
		strcpy(indexI_J[3][2].myChar, "4_3");
		strcpy(indexI_J[3][3].myChar, "4_4");
		strcpy(indexI_J[3][4].myChar, "4_5");
		strcpy(indexI_J[3][5].myChar, "4_6");
		strcpy(indexI_J[3][6].myChar, "4_7");
		strcpy(indexI_J[3][7].myChar, "4_8");
		strcpy(indexI_J[3][8].myChar, "4_9");
		strcpy(indexI_J[3][9].myChar, "4_10");
		strcpy(indexI_J[3][10].myChar, "4_11");
		strcpy(indexI_J[3][11].myChar, "4_12");
		strcpy(indexI_J[3][12].myChar, "4_13");
		strcpy(indexI_J[3][13].myChar, "4_14");
		strcpy(indexI_J[3][14].myChar, "4_15");
		strcpy(indexI_J[3][15].myChar, "4_16");
		strcpy(indexI_J[3][16].myChar, "4_17");
		strcpy(indexI_J[3][17].myChar, "4_18");
		strcpy(indexI_J[3][18].myChar, "4_19");
		strcpy(indexI_J[3][19].myChar, "4_20");
		strcpy(indexI_J[3][20].myChar, "4_21");
		strcpy(indexI_J[3][21].myChar, "4_22");
		strcpy(indexI_J[3][22].myChar, "4_23");
		strcpy(indexI_J[3][23].myChar, "4_24");
		strcpy(indexI_J[3][24].myChar, "4_25");
		strcpy(indexI_J[3][25].myChar, "4_26");
		strcpy(indexI_J[3][26].myChar, "4_27");
		strcpy(indexI_J[3][27].myChar, "4_28");
		strcpy(indexI_J[3][28].myChar, "4_29");
		strcpy(indexI_J[3][29].myChar, "4_30");


		strcpy(indexI_J[4][0].myChar, "5_1");
		strcpy(indexI_J[4][1].myChar, "5_2");
		strcpy(indexI_J[4][2].myChar, "5_3");
		strcpy(indexI_J[4][3].myChar, "5_4");
		strcpy(indexI_J[4][4].myChar, "5_5");
		strcpy(indexI_J[4][5].myChar, "5_6");
		strcpy(indexI_J[4][6].myChar, "5_7");
		strcpy(indexI_J[4][7].myChar, "5_8");
		strcpy(indexI_J[4][8].myChar, "5_9");
		strcpy(indexI_J[4][9].myChar, "5_10");
		strcpy(indexI_J[4][10].myChar, "5_11");
		strcpy(indexI_J[4][11].myChar, "5_12");
		strcpy(indexI_J[4][12].myChar, "5_13");
		strcpy(indexI_J[4][13].myChar, "5_14");
		strcpy(indexI_J[4][14].myChar, "5_15");
		strcpy(indexI_J[4][15].myChar, "5_16");
		strcpy(indexI_J[4][16].myChar, "5_17");
		strcpy(indexI_J[4][17].myChar, "5_18");
		strcpy(indexI_J[4][18].myChar, "5_19");
		strcpy(indexI_J[4][19].myChar, "5_20");
		strcpy(indexI_J[4][20].myChar, "5_21");
		strcpy(indexI_J[4][21].myChar, "5_22");
		strcpy(indexI_J[4][22].myChar, "5_23");
		strcpy(indexI_J[4][23].myChar, "5_24");
		strcpy(indexI_J[4][24].myChar, "5_25");
		strcpy(indexI_J[4][25].myChar, "5_26");
		strcpy(indexI_J[4][26].myChar, "5_27");
		strcpy(indexI_J[4][27].myChar, "5_28");
		strcpy(indexI_J[4][28].myChar, "5_29");
		strcpy(indexI_J[4][29].myChar, "5_30");


		strcpy(indexI_J[5][0].myChar, "6_1");
		strcpy(indexI_J[5][1].myChar, "6_2");
		strcpy(indexI_J[5][2].myChar, "6_3");
		strcpy(indexI_J[5][3].myChar, "6_4");
		strcpy(indexI_J[5][4].myChar, "6_5");
		strcpy(indexI_J[5][5].myChar, "6_6");
		strcpy(indexI_J[5][6].myChar, "6_7");
		strcpy(indexI_J[5][7].myChar, "6_8");
		strcpy(indexI_J[5][8].myChar, "6_9");
		strcpy(indexI_J[5][9].myChar, "6_10");
		strcpy(indexI_J[5][10].myChar, "6_11");
		strcpy(indexI_J[5][11].myChar, "6_12");
		strcpy(indexI_J[5][12].myChar, "6_13");
		strcpy(indexI_J[5][13].myChar, "6_14");
		strcpy(indexI_J[5][14].myChar, "6_15");
		strcpy(indexI_J[5][15].myChar, "6_16");
		strcpy(indexI_J[5][16].myChar, "6_17");
		strcpy(indexI_J[5][17].myChar, "6_18");
		strcpy(indexI_J[5][18].myChar, "6_19");
		strcpy(indexI_J[5][19].myChar, "6_20");
		strcpy(indexI_J[5][20].myChar, "6_21");
		strcpy(indexI_J[5][21].myChar, "6_22");
		strcpy(indexI_J[5][22].myChar, "6_23");
		strcpy(indexI_J[5][23].myChar, "6_24");
		strcpy(indexI_J[5][24].myChar, "6_25");
		strcpy(indexI_J[5][25].myChar, "6_26");
		strcpy(indexI_J[5][26].myChar, "6_27");
		strcpy(indexI_J[5][27].myChar, "6_28");
		strcpy(indexI_J[5][28].myChar, "6_29");
		strcpy(indexI_J[5][29].myChar, "6_30");


		strcpy(indexI_J[6][0].myChar, "7_1");
		strcpy(indexI_J[6][1].myChar, "7_2");
		strcpy(indexI_J[6][2].myChar, "7_3");
		strcpy(indexI_J[6][3].myChar, "7_4");
		strcpy(indexI_J[6][4].myChar, "7_5");
		strcpy(indexI_J[6][5].myChar, "7_6");
		strcpy(indexI_J[6][6].myChar, "7_7");
		strcpy(indexI_J[6][7].myChar, "7_8");
		strcpy(indexI_J[6][8].myChar, "7_9");
		strcpy(indexI_J[6][9].myChar, "7_10");
		strcpy(indexI_J[6][10].myChar, "7_11");
		strcpy(indexI_J[6][11].myChar, "7_12");
		strcpy(indexI_J[6][12].myChar, "7_13");
		strcpy(indexI_J[6][13].myChar, "7_14");
		strcpy(indexI_J[6][14].myChar, "7_15");
		strcpy(indexI_J[6][15].myChar, "7_16");
		strcpy(indexI_J[6][16].myChar, "7_17");
		strcpy(indexI_J[6][17].myChar, "7_18");
		strcpy(indexI_J[6][18].myChar, "7_19");
		strcpy(indexI_J[6][19].myChar, "7_20");
		strcpy(indexI_J[6][20].myChar, "7_21");
		strcpy(indexI_J[6][21].myChar, "7_22");
		strcpy(indexI_J[6][22].myChar, "7_23");
		strcpy(indexI_J[6][23].myChar, "7_24");
		strcpy(indexI_J[6][24].myChar, "7_25");
		strcpy(indexI_J[6][25].myChar, "7_26");
		strcpy(indexI_J[6][26].myChar, "7_27");
		strcpy(indexI_J[6][27].myChar, "7_28");
		strcpy(indexI_J[6][28].myChar, "7_29");
		strcpy(indexI_J[6][29].myChar, "7_30");


		strcpy(indexI_J[7][0].myChar, "8_1");
		strcpy(indexI_J[7][1].myChar, "8_2");
		strcpy(indexI_J[7][2].myChar, "8_3");
		strcpy(indexI_J[7][3].myChar, "8_4");
		strcpy(indexI_J[7][4].myChar, "8_5");
		strcpy(indexI_J[7][5].myChar, "8_6");
		strcpy(indexI_J[7][6].myChar, "8_7");
		strcpy(indexI_J[7][7].myChar, "8_8");
		strcpy(indexI_J[7][8].myChar, "8_9");
		strcpy(indexI_J[7][9].myChar, "8_10");
		strcpy(indexI_J[7][10].myChar, "8_11");
		strcpy(indexI_J[7][11].myChar, "8_12");
		strcpy(indexI_J[7][12].myChar, "8_13");
		strcpy(indexI_J[7][13].myChar, "8_14");
		strcpy(indexI_J[7][14].myChar, "8_15");
		strcpy(indexI_J[7][15].myChar, "8_16");
		strcpy(indexI_J[7][16].myChar, "8_17");
		strcpy(indexI_J[7][17].myChar, "8_18");
		strcpy(indexI_J[7][18].myChar, "8_19");
		strcpy(indexI_J[7][19].myChar, "8_20");
		strcpy(indexI_J[7][20].myChar, "8_21");
		strcpy(indexI_J[7][21].myChar, "8_22");
		strcpy(indexI_J[7][22].myChar, "8_23");
		strcpy(indexI_J[7][23].myChar, "8_24");
		strcpy(indexI_J[7][24].myChar, "8_25");
		strcpy(indexI_J[7][25].myChar, "8_26");
		strcpy(indexI_J[7][26].myChar, "8_27");
		strcpy(indexI_J[7][27].myChar, "8_28");
		strcpy(indexI_J[7][28].myChar, "8_29");
		strcpy(indexI_J[7][29].myChar, "8_30");

		strcpy(indexI_J[8][0].myChar, "9_1");
		strcpy(indexI_J[8][1].myChar, "9_2");
		strcpy(indexI_J[8][2].myChar, "9_3");
		strcpy(indexI_J[8][3].myChar, "9_4");
		strcpy(indexI_J[8][4].myChar, "9_5");
		strcpy(indexI_J[8][5].myChar, "9_6");
		strcpy(indexI_J[8][6].myChar, "9_7");
		strcpy(indexI_J[8][7].myChar, "9_8");
		strcpy(indexI_J[8][8].myChar, "9_9");
		strcpy(indexI_J[8][9].myChar, "9_10");
		strcpy(indexI_J[8][10].myChar, "9_11");
		strcpy(indexI_J[8][11].myChar, "9_12");
		strcpy(indexI_J[8][12].myChar, "9_13");
		strcpy(indexI_J[8][13].myChar, "9_14");
		strcpy(indexI_J[8][14].myChar, "9_15");
		strcpy(indexI_J[8][15].myChar, "9_16");
		strcpy(indexI_J[8][16].myChar, "9_17");
		strcpy(indexI_J[8][17].myChar, "9_18");
		strcpy(indexI_J[8][18].myChar, "9_19");
		strcpy(indexI_J[8][19].myChar, "9_20");
		strcpy(indexI_J[8][20].myChar, "9_21");
		strcpy(indexI_J[8][21].myChar, "9_22");
		strcpy(indexI_J[8][22].myChar, "9_23");
		strcpy(indexI_J[8][23].myChar, "9_24");
		strcpy(indexI_J[8][24].myChar, "9_25");
		strcpy(indexI_J[8][25].myChar, "9_26");
		strcpy(indexI_J[8][26].myChar, "9_27");
		strcpy(indexI_J[8][27].myChar, "9_28");
		strcpy(indexI_J[8][28].myChar, "9_29");
		strcpy(indexI_J[8][29].myChar, "9_30");


		strcpy(indexI_J[9][0].myChar, "10_1");
		strcpy(indexI_J[9][1].myChar, "10_2");
		strcpy(indexI_J[9][2].myChar, "10_3");
		strcpy(indexI_J[9][3].myChar, "10_4");
		strcpy(indexI_J[9][4].myChar, "10_5");
		strcpy(indexI_J[9][5].myChar, "10_6");
		strcpy(indexI_J[9][6].myChar, "10_7");
		strcpy(indexI_J[9][7].myChar, "10_8");
		strcpy(indexI_J[9][8].myChar, "10_9");
		strcpy(indexI_J[9][9].myChar, "10_10");
		strcpy(indexI_J[9][10].myChar, "10_11");
		strcpy(indexI_J[9][11].myChar, "10_12");
		strcpy(indexI_J[9][12].myChar, "10_13");
		strcpy(indexI_J[9][13].myChar, "10_14");
		strcpy(indexI_J[9][14].myChar, "10_15");
		strcpy(indexI_J[9][15].myChar, "10_16");
		strcpy(indexI_J[9][16].myChar, "10_17");
		strcpy(indexI_J[9][17].myChar, "10_18");
		strcpy(indexI_J[9][18].myChar, "10_19");
		strcpy(indexI_J[9][19].myChar, "10_20");

		strcpy(indexI_J[10][0].myChar, "11_1");
		strcpy(indexI_J[10][1].myChar, "11_2");
		strcpy(indexI_J[10][2].myChar, "11_3");
		strcpy(indexI_J[10][3].myChar, "11_4");
		strcpy(indexI_J[10][4].myChar, "11_5");
		strcpy(indexI_J[10][5].myChar, "11_6");
		strcpy(indexI_J[10][6].myChar, "11_7");
		strcpy(indexI_J[10][7].myChar, "11_8");
		strcpy(indexI_J[10][8].myChar, "11_9");
		strcpy(indexI_J[10][9].myChar, "11_10");
		strcpy(indexI_J[10][10].myChar, "11_11");
		strcpy(indexI_J[10][11].myChar, "11_12");
		strcpy(indexI_J[10][12].myChar, "11_13");
		strcpy(indexI_J[10][13].myChar, "11_14");
		strcpy(indexI_J[10][14].myChar, "11_15");
		strcpy(indexI_J[10][15].myChar, "11_16");
		strcpy(indexI_J[10][16].myChar, "11_17");
		strcpy(indexI_J[10][17].myChar, "11_18");
		strcpy(indexI_J[10][18].myChar, "11_19");
		strcpy(indexI_J[10][19].myChar, "11_20");

		strcpy(indexI_J[11][0].myChar, "12_1");
		strcpy(indexI_J[11][1].myChar, "12_2");
		strcpy(indexI_J[11][2].myChar, "12_3");
		strcpy(indexI_J[11][3].myChar, "12_4");
		strcpy(indexI_J[11][4].myChar, "12_5");
		strcpy(indexI_J[11][5].myChar, "12_6");
		strcpy(indexI_J[11][6].myChar, "12_7");
		strcpy(indexI_J[11][7].myChar, "12_8");
		strcpy(indexI_J[11][8].myChar, "12_9");
		strcpy(indexI_J[11][9].myChar, "12_10");
		strcpy(indexI_J[11][10].myChar, "12_11");
		strcpy(indexI_J[11][11].myChar, "12_12");
		strcpy(indexI_J[11][12].myChar, "12_13");
		strcpy(indexI_J[11][13].myChar, "12_14");
		strcpy(indexI_J[11][14].myChar, "12_15");
		strcpy(indexI_J[11][15].myChar, "12_16");
		strcpy(indexI_J[11][16].myChar, "12_17");
		strcpy(indexI_J[11][17].myChar, "12_18");
		strcpy(indexI_J[11][18].myChar, "12_19");
		strcpy(indexI_J[11][19].myChar, "12_20");

		strcpy(indexI_J[12][0].myChar, "13_1");
		strcpy(indexI_J[12][1].myChar, "13_2");
		strcpy(indexI_J[12][2].myChar, "13_3");
		strcpy(indexI_J[12][3].myChar, "13_4");
		strcpy(indexI_J[12][4].myChar, "13_5");
		strcpy(indexI_J[12][5].myChar, "13_6");
		strcpy(indexI_J[12][6].myChar, "13_7");
		strcpy(indexI_J[12][7].myChar, "13_8");
		strcpy(indexI_J[12][8].myChar, "13_9");
		strcpy(indexI_J[12][9].myChar, "13_10");
		strcpy(indexI_J[12][10].myChar, "13_11");
		strcpy(indexI_J[12][11].myChar, "13_12");
		strcpy(indexI_J[12][12].myChar, "13_13");
		strcpy(indexI_J[12][13].myChar, "13_14");
		strcpy(indexI_J[12][14].myChar, "13_15");
		strcpy(indexI_J[12][15].myChar, "13_16");
		strcpy(indexI_J[12][16].myChar, "13_17");
		strcpy(indexI_J[12][17].myChar, "13_18");
		strcpy(indexI_J[12][18].myChar, "13_19");
		strcpy(indexI_J[12][19].myChar, "13_20");

		strcpy(indexI_J[13][0].myChar, "14_1");
		strcpy(indexI_J[13][1].myChar, "14_2");
		strcpy(indexI_J[13][2].myChar, "14_3");
		strcpy(indexI_J[13][3].myChar, "14_4");
		strcpy(indexI_J[13][4].myChar, "14_5");
		strcpy(indexI_J[13][5].myChar, "14_6");
		strcpy(indexI_J[13][6].myChar, "14_7");
		strcpy(indexI_J[13][7].myChar, "14_8");
		strcpy(indexI_J[13][8].myChar, "14_9");
		strcpy(indexI_J[13][9].myChar, "14_10");
		strcpy(indexI_J[13][10].myChar, "14_11");
		strcpy(indexI_J[13][11].myChar, "14_12");
		strcpy(indexI_J[13][12].myChar, "14_13");
		strcpy(indexI_J[13][13].myChar, "14_14");
		strcpy(indexI_J[13][14].myChar, "14_15");
		strcpy(indexI_J[13][15].myChar, "14_16");
		strcpy(indexI_J[13][16].myChar, "14_17");
		strcpy(indexI_J[13][17].myChar, "14_18");
		strcpy(indexI_J[13][18].myChar, "14_19");
		strcpy(indexI_J[13][19].myChar, "14_20");

		strcpy(indexI_J[14][0].myChar, "15_1");
		strcpy(indexI_J[14][1].myChar, "15_2");
		strcpy(indexI_J[14][2].myChar, "15_3");
		strcpy(indexI_J[14][3].myChar, "15_4");
		strcpy(indexI_J[14][4].myChar, "15_5");
		strcpy(indexI_J[14][5].myChar, "15_6");
		strcpy(indexI_J[14][6].myChar, "15_7");
		strcpy(indexI_J[14][7].myChar, "15_8");
		strcpy(indexI_J[14][8].myChar, "15_9");
		strcpy(indexI_J[14][9].myChar, "15_10");
		strcpy(indexI_J[14][10].myChar, "15_11");
		strcpy(indexI_J[14][11].myChar, "15_12");
		strcpy(indexI_J[14][12].myChar, "15_13");
		strcpy(indexI_J[14][13].myChar, "15_14");
		strcpy(indexI_J[14][14].myChar, "15_15");
		strcpy(indexI_J[14][15].myChar, "15_16");
		strcpy(indexI_J[14][16].myChar, "15_17");
		strcpy(indexI_J[14][17].myChar, "15_18");
		strcpy(indexI_J[14][18].myChar, "15_19");
		strcpy(indexI_J[14][19].myChar, "15_20");

		strcpy(indexI_J[15][0].myChar, "16_1");
		strcpy(indexI_J[15][1].myChar, "16_2");
		strcpy(indexI_J[15][2].myChar, "16_3");
		strcpy(indexI_J[15][3].myChar, "16_4");
		strcpy(indexI_J[15][4].myChar, "16_5");
		strcpy(indexI_J[15][5].myChar, "16_6");
		strcpy(indexI_J[15][6].myChar, "16_7");
		strcpy(indexI_J[15][7].myChar, "16_8");
		strcpy(indexI_J[15][8].myChar, "16_9");
		strcpy(indexI_J[15][9].myChar, "16_10");
		strcpy(indexI_J[15][10].myChar, "16_11");
		strcpy(indexI_J[15][11].myChar, "16_12");
		strcpy(indexI_J[15][12].myChar, "16_13");
		strcpy(indexI_J[15][13].myChar, "16_14");
		strcpy(indexI_J[15][14].myChar, "16_15");
		strcpy(indexI_J[15][15].myChar, "16_16");
		strcpy(indexI_J[15][16].myChar, "16_17");
		strcpy(indexI_J[15][17].myChar, "16_18");
		strcpy(indexI_J[15][18].myChar, "16_19");
		strcpy(indexI_J[15][19].myChar, "16_20");

		strcpy(indexI_J[16][0].myChar, "17_1");
		strcpy(indexI_J[16][1].myChar, "17_2");
		strcpy(indexI_J[16][2].myChar, "17_3");
		strcpy(indexI_J[16][3].myChar, "17_4");
		strcpy(indexI_J[16][4].myChar, "17_5");
		strcpy(indexI_J[16][5].myChar, "17_6");
		strcpy(indexI_J[16][6].myChar, "17_7");
		strcpy(indexI_J[16][7].myChar, "17_8");
		strcpy(indexI_J[16][8].myChar, "17_9");
		strcpy(indexI_J[16][9].myChar, "17_10");
		strcpy(indexI_J[16][10].myChar, "17_11");
		strcpy(indexI_J[16][11].myChar, "17_12");
		strcpy(indexI_J[16][12].myChar, "17_13");
		strcpy(indexI_J[16][13].myChar, "17_14");
		strcpy(indexI_J[16][14].myChar, "17_15");
		strcpy(indexI_J[16][15].myChar, "17_16");
		strcpy(indexI_J[16][16].myChar, "17_17");
		strcpy(indexI_J[16][17].myChar, "17_18");
		strcpy(indexI_J[16][18].myChar, "17_19");
		strcpy(indexI_J[16][19].myChar, "17_20");

		strcpy(indexI_J[17][0].myChar, "18_1");
		strcpy(indexI_J[17][1].myChar, "18_2");
		strcpy(indexI_J[17][2].myChar, "18_3");
		strcpy(indexI_J[17][3].myChar, "18_4");
		strcpy(indexI_J[17][4].myChar, "18_5");
		strcpy(indexI_J[17][5].myChar, "18_6");
		strcpy(indexI_J[17][6].myChar, "18_7");
		strcpy(indexI_J[17][7].myChar, "18_8");
		strcpy(indexI_J[17][8].myChar, "18_9");
		strcpy(indexI_J[17][9].myChar, "18_10");
		strcpy(indexI_J[17][10].myChar, "18_11");
		strcpy(indexI_J[17][11].myChar, "18_12");
		strcpy(indexI_J[17][12].myChar, "18_13");
		strcpy(indexI_J[17][13].myChar, "18_14");
		strcpy(indexI_J[17][14].myChar, "18_15");
		strcpy(indexI_J[17][15].myChar, "18_16");
		strcpy(indexI_J[17][16].myChar, "18_17");
		strcpy(indexI_J[17][17].myChar, "18_18");
		strcpy(indexI_J[17][18].myChar, "18_19");
		strcpy(indexI_J[17][19].myChar, "18_20");
		return 0;
	} //end assign indexI_J

	int AssignMatrixIJ(myString MatrixIJ[18][30],myString indexIJ[18][30],char Mat[],int BladeCnt,int bladeCutCnt[200] )
	{

		int I,J;
		for (I=0;I<BladeCnt;I++)
		{
			for (J=0;J<bladeCutCnt[I];J++)
			{
				strcpy(MatrixIJ[I][J].myChar, Mat);
				strcpy (MatrixIJ[I][J].myChar+strlen(MatrixIJ[I][J].myChar),indexIJ[I][J].myChar);
			//	cout<<MatrixIJ[I][J].myChar<<endl;
			}
		}
		return 0;
	}

