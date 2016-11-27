//REGION A DATA 2D HISTOGRAMS ARE NOT BLINDED!!!  BEWARE!!!
#include <string>
#include <map>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "THStack.h"
#include "TProfile.h"
#include "TF1.h"
#include "TKey.h"
#include "RooRealVar.h"
#include "RooGaussian.h"
#include "RooExponential.h"
#include "RooAddPdf.h"
#include "RooDataHist.h"
#include "RooPlot.h"
#include "RooFitResult.h"
#include "RooBinning.h"
#include "Plot.C"
void formatDataBkgPlots(const string& inputVersion, const string& outputVersion,  const string& MTBin)
{
  //initial
  gROOT->Reset();

  //get CMSSW path
  const char* CMSSWPathCString = gSystem->Getenv("CMSSW_BASE");
  if (!CMSSWPathCString) {
    CMSSWPathCString = "";
    cout << "Error: environment variable CMSSW_BASE is not set.  ";
    cout << "Please run cmsenv from within your CMSSW project area.\n";
  }
  string CMSSWPathCPPString(CMSSWPathCString);


  //needed so vector<Color_t> and vector<Style_t> work

  //set up canvas and graph names and blinded bins for data
  vector<string> canvasNames1D;
  canvasNames1D.push_back("muHadMassCanvas");
  vector<string> graphNames1D;
  graphNames1D.push_back("muHadMass");

  vector<Int_t> nullBlindLow(canvasNames1D.size(), 0);
  vector<Int_t> nullBlindHigh(canvasNames1D.size(), -2);

  //set up plot style options
  vector<string> legendHeaders19p7InvFb(canvasNames1D.size(), "Normalized to 19.7 fb^{-1}");
  vector<Color_t> colorsMCData;
  colorsMCData.push_back(kCyan + 2); //ZZ
  colorsMCData.push_back(kBlue + 1); //Drell-Yan
  vector<Style_t> styles;
  styles.push_back(22); //ZZ
  styles.push_back(27); //Drell-Yan
  vector<string> legendEntriesMCData;
  legendEntriesMCData.push_back("Data 19.7 fb^{-1}");
  legendEntriesMCData.push_back("ZZ");
  legendEntriesMCData.push_back("Drell-Yan + jets");
  const bool setLogY = true;
  const bool drawStack = true;
  const bool drawSame = false;
  const bool dataMC = false;

  //best available weights according to Dropbox spreadsheet
  vector<float> weightsMCData(2.0,1.0 ); //MC samples already properly weighted during hadding
  cout<<"weightsMCData.size()="<<weightsMCData.size()<<std::endl;
  //space-saving constant definitions
  string user(gSystem->GetFromPipe("whoami").Data());
  const string analysisFilePath("/afs/cern.ch/work/m/" + user+"/public/data1/");
  const string fileExt(".root");
  const string tag19p7InvFb("_19p7fb-1");
  const string tag1("_normalizedTo1");

  //version tags
  const string outputVTag("_" + outputVersion);
  const string TTJetsVTag("_" + inputVersion);
  const string ZZVTag("_" + inputVersion);
  const string DYJetsToLLVTag("_" + inputVersion);

  cout << "Begin hadding...\n";



  //"hadd" ZZ sample just to get the formatting of the 2D plots the same
  cout << "...ZZ\n";
  string ZZSuffix(ZZVTag + fileExt);
  string ZZAllPrefix(analysisFilePath + "ZZ/analysis/muHadAnalysis" + MTBin + "_ZZ");
  string ZZAllHaddOutputFile(ZZAllPrefix + "_hadd" + ZZSuffix);
  vector<string> ZZAllHaddInputFiles;
  stringstream ZZAllName;
  ZZAllName << ZZAllPrefix << ZZSuffix;
  ZZAllHaddInputFiles.push_back(ZZAllName.str());
  haddCanvases(ZZAllHaddOutputFile, ZZAllHaddInputFiles, 
	       vector<float>(1,0.00313), canvasNames1D, graphNames1D, 
	       nullBlindLow, nullBlindHigh);


cout << "...Drell-Yan\n";
  string DYJetsToLLSuffix(DYJetsToLLVTag + fileExt);
  string DYJetsToLLAllPrefix(analysisFilePath + "DYLow/analysis/muHadAnalysis" + MTBin + 
			     "_DYLow");
  string DYJetsToLLAllHaddOutputFile(DYJetsToLLAllPrefix + "_hadd"+ DYJetsToLLSuffix);
  vector<string> DYJetsToLLAllHaddInputFiles;
  stringstream DYJetsToLLAllName;
  DYJetsToLLAllName << DYJetsToLLAllPrefix <<  DYJetsToLLSuffix;
  DYJetsToLLAllHaddInputFiles.push_back(DYJetsToLLAllName.str());
  haddCanvases(DYJetsToLLAllHaddOutputFile, DYJetsToLLAllHaddInputFiles, 
	       vector<float>(1,12.04), canvasNames1D, graphNames1D, nullBlindLow, nullBlindHigh);
  
  string dataVsMCOutputFile(analysisFilePath + "results/dataVsMC_muHadAllAnalysis" + MTBin +
                            tag19p7InvFb + outputVTag + fileExt);
  vector<string> dataVsMCInputFiles;
  dataVsMCInputFiles.push_back(ZZAllHaddOutputFile);
  dataVsMCInputFiles.push_back(DYJetsToLLAllHaddOutputFile);
  cout << "\nPlot data vs. MC normalized to data luminosity\n---\n";
  drawMultipleEfficiencyGraphsOn1Canvas(dataVsMCOutputFile, dataVsMCInputFiles,
                                        canvasNames1D, graphNames1D, legendHeaders19p7InvFb,
                                        colorsMCData, styles, legendEntriesMCData,
                                        weightsMCData, setLogY, drawStack, dataMC);
}
