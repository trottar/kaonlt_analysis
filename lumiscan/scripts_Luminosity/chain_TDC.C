//xR__LOAD_LIBRARY(libTreePlayer)
#include <string>
#include <cstdio>
#include <iostream>
#include "TFile.h"
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>
#include <TH1.h>
#include <TH2.h>
#include <TCanvas.h>


void chain_TDC(Int_t runNum = 0){

  if(runNum==0){
  
  	cout << "Please enter run number ...\n";
  	cin >> runNum;
  }

  //Luminosity replay files
  TString rootNOREF = Form("~/ResearchNP/ROOTAnalysis/ROOTfiles/KaonLT_Luminosity_coin_replay_production_NOREF_%i_-1.root",runNum);
  TString rootREF = Form("~/ResearchNP/ROOTAnalysis/ROOTfiles/KaonLT_Luminosity_coin_replay_production_%i_-1.root",runNum);
  //TString rootREF = Form("~/ResearchNP/ROOTAnalysis/ROOTfiles/KaonLT_Luminosity_coin_replay_production_NOREF_%i_-1.root",runNum);
  
  TString outputpdf;
  TString outputroot;
  TString foutname;

  TFile *out;
	
  TTree *Ttrig;
  TTree *Tedtm;
  TTree *Tscaler;

  //Leaves that will be used, defined below
  TString tdc_TRIG1_tdcTime;
  TString tdc_TRIG3_tdcTime;
  TString tdc_TRIG1_tdcTimeRaw;
  TString tdc_TRIG3_tdcTimeRaw;
  TString EDTM_TRIG1_tdcTime;
  TString EDTM_TRIG3_tdcTime;
  TString EDTM_TRIG1_tdcTimeRaw;
  TString EDTM_TRIG3_tdcTimeRaw;
  
  TCanvas *ctdcTime1;
  TCanvas *ctdcTime3;
  TCanvas *ctdcTime1Raw;
  TCanvas *ctdcTime3Raw;
  TCanvas *cedtm1;
  TCanvas *cedtm3;
  TCanvas *cedtm1Raw;
  TCanvas *cedtm3Raw;
	
  TH1F *htrig1_NOREF;
  TH1F *htrig3_NOREF;
  TH1F *htrig1_REF;
  TH1F *htrig3_REF;
  TH1F *htrig1Raw_NOREF;
  TH1F *htrig3Raw_NOREF;
  TH1F *htrig1Raw_REF;
  TH1F *htrig3Raw_REF;
  TH1F *hedtm1_NOREF;
  TH1F *hedtm3_NOREF;
  TH1F *hedtm1_REF;
  TH1F *hedtm3_REF;
  TH1F *hedtm1Raw_NOREF;
  TH1F *hedtm3Raw_NOREF;
  TH1F *hedtm1Raw_REF;
  TH1F *hedtm3Raw_REF;

  TH2F *trig1v3NOREF;
  TH2F *trig1v3REF;
  TH2F *trig1v3REF_EDTMCUT;
  TH2F *trig1v3REF_NOCUT;
  TH2F *edtm1v3NOREF;
  TH2F *edtm1v3REF;
  TH2F *edtm1v3REF_NOCUT;

  foutname = Form("trigPlots_%i_all",runNum);
  outputpdf = "OUTPUT/" + foutname + ".pdf";
  outputroot = "OUTPUT/" + foutname + ".root";

  //Output root file with new plots
  out = new TFile(outputroot,"RECREATE");
  gFile = out;

  //Imported leaves from replay (defined above)
  tdc_TRIG1_tdcTime = "T.coin.pTRIG1_ROC2_tdcTime";
  tdc_TRIG3_tdcTime = "T.coin.pTRIG3_ROC1_tdcTime";
  tdc_TRIG1_tdcTimeRaw = "T.coin.pTRIG1_ROC2_tdcTimeRaw";
  tdc_TRIG3_tdcTimeRaw = "T.coin.pTRIG3_ROC1_tdcTimeRaw";
  
  Ttrig = new TTree("TRIG","Plots of TDC's");
  
  ctdcTime1 = new TCanvas("ctdcTime1","TRIG1 Plots", 600, 400);
  ctdcTime3 = new TCanvas("ctdcTime3","TRIG3 Plots", 600, 400);
  ctdcTime1Raw = new TCanvas("ctdcTime1Raw","Raw TRIG1 Plots", 600, 400);
  ctdcTime3Raw = new TCanvas("ctdcTime3Raw","Raw TRIG3 Plots", 600, 400);
  
  htrig1_NOREF = new TH1F("T.coin.pTRIG1_ROC2_tdcTime[NO REF]","T.coin.pTRIG1_ROC2_tdcTime[NO REF]", 500,-600, 600);
  htrig3_NOREF = new TH1F("T.coin.pTRIG3_ROC1_tdcTime[NO REF]","T.coin.pTRIG3_ROC1_tdcTime[NO REF]", 500,-600, 600);
  htrig1_REF = new TH1F("T.coin.pTRIG1_ROC2_tdcTime[REF]","T.coin.pTRIG1_ROC2_tdcTime[REF]", 500,-600, 600);
  htrig3_REF = new TH1F("T.coin.pTRIG3_ROC1_tdcTime[REF]","T.coin.pTRIG3_ROC1_tdcTime[REF]", 500,-600, 600);
  htrig1Raw_NOREF = new TH1F("T.coin.pTRIG1_ROC2_tdcTimeRaw[NO REF]","T.coin.pTRIG1_ROC2_tdcTimeRaw[NO REF]", 500,-600, 10000);
  htrig3Raw_NOREF = new TH1F("T.coin.pTRIG3_ROC1_tdcTimeRaw[NO REF]","T.coin.pTRIG3_ROC1_tdcTimeRaw[NO REF]", 500,-600, 10000);
  htrig1Raw_REF = new TH1F("T.coin.pTRIG1_ROC2_tdcTimeRaw[REF]","T.coin.pTRIG1_ROC2_tdcTimeRaw[REF]", 500,-600, 10000);
  htrig3Raw_REF = new TH1F("T.coin.pTRIG3_ROC1_tdcTimeRaw[REF]","T.coin.pTRIG3_ROC1_tdcTimeRaw[REF]", 500,-600, 10000);

  EDTM_TRIG1_tdcTime = "T.coin.pEDTM_tdcTime";
  EDTM_TRIG3_tdcTime = "T.coin.pEDTM_tdcTime";
  EDTM_TRIG1_tdcTimeRaw = "T.coin.pEDTM_tdcTimeRaw";
  EDTM_TRIG3_tdcTimeRaw = "T.coin.pEDTM_tdcTimeRaw";
  
  Tedtm = new TTree("EDTM","Plots of EDTM's");
  
  cedtm1 = new TCanvas("cedtm1","EDTM1 Plots", 600, 400);
  cedtm3 = new TCanvas("cedtm3","EDTM3 Plots", 600, 400);
  cedtm1Raw = new TCanvas("cedtm1Raw","EDTM1 Raw Plots", 600, 400);
  cedtm3Raw = new TCanvas("cedtm3Raw","EDTM3 Raw Plots", 600, 400);
  
  hedtm1_NOREF = new TH1F("T.coin.pEDTM_tdcTime[NO REF TRIG1]","T.coin.pEDTM_tdcTime[NO REF TRIG1]", 500,-600, 600);
  hedtm3_NOREF = new TH1F("T.coin.pEDTM_tdcTime[NO REF TRIG3]","T.coin.pEDTM_tdcTime[NO REF TRIG3]", 500,-600, 600);
  hedtm1_REF = new TH1F("T.coin.pEDTM_tdcTime[REF TRIG1]","T.coin.pEDTM_tdcTime[REF TRIG1]", 500,-600, 600);
  hedtm3_REF = new TH1F("T.coin.pEDTM_tdcTime[REF TRIG3]","T.coin.pEDTM_tdcTime[REF TRIG3]", 500,-600, 600);
  hedtm1Raw_NOREF = new TH1F("T.coin.pEDTM_tdcTimeRaw[NO REF TRIG1]","T.coin.pEDTM_tdcTimeRaw[NO REF TRIG1]", 500,-600, 10000);
  hedtm3Raw_NOREF = new TH1F("T.coin.pEDTM_tdcTimeRaw[NO REF TRIG3]","T.coin.pEDTM_tdcTimeRaw[NO REF TRIG3]", 500,-600, 10000);
  hedtm1Raw_REF = new TH1F("T.coin.pEDTM_tdcTimeRaw[REF TRIG1]","T.coin.pEDTM_tdcTimeRaw[REF TRIG3]", 500,-600, 10000);
  hedtm3Raw_REF = new TH1F("T.coin.pEDTM_tdcTimeRaw[REF TRIG3]","T.coin.pEDTM_tdcTimeRaw[REF TRIG3]", 500,-600, 10000);

  trig1v3NOREF = new TH2F("T.coin.pTRIG1-pTRIG3[NO REF]","T.coin.pTRIG1-pTRIG3[NO REF]", 500,0, 600,500,0, 600);
  trig1v3REF = new TH2F("T.coin.pTRIG1-pTRIG3[REF]","T.coin.pTRIG1-pTRIG3[REF]", 500,0, 600,500,0, 600);
  trig1v3REF_NOCUT = new TH2F("T.coin.pTRIG1-pTRIG3[REF NO CUT]","T.coin.pTRIG1-pTRIG3[REF NO CUT]", 500,0, 600,500,0, 600);
  trig1v3REF_EDTMCUT = new TH2F("T.coin.pTRIG1-pTRIG3[REF EDTM CUT]","T.coin.pTRIG1-pTRIG3[REF EDTM CUT]", 500,0, 600,500,0, 600);
  edtm1v3NOREF = new TH2F("T.coin.pEDTM1-pEDTM3[NO REF]","T.coin.pEDTM1-pEDTM3[NO REF]", 500,0, 600,500,0, 600);
  edtm1v3REF = new TH2F("T.coin.pEDTM1-pEDTM3[REF]","T.coin.pEDTM1-pEDTM3[REF]", 500,0, 600,500,0, 600);
  edtm1v3REF_NOCUT = new TH2F("T.coin.pEDTM1-pEDTM3[REF NO CUT]","T.coin.pEDTM1-pEDTM3[REF NO CUT]", 500,0, 600,500,0, 600);

  Tscaler = new TTree("Scalers","Plots of Scalers");
  
  TFile *f1 = TFile::Open(rootNOREF);
  if( !f1 || f1->IsZombie()){
	return;
  }else f1->GetName();

  TFile *f2 = TFile::Open(rootREF);
  if( !f2 || f2->IsZombie()){
	return;
  }else f2->GetName();

  TTreeReader readNOREF("T", f1);
  TTreeReader readREF("T", f2);
  TTreeReader tsp("TSP", f2);  
  TTreeReader tsh("TSH", f2);

  //Used for histogram creation
  TTreeReaderValue<Double_t> trig1_NOREF(readNOREF, tdc_TRIG1_tdcTime);
  TTreeReaderValue<Double_t> trig3_NOREF(readNOREF, tdc_TRIG3_tdcTime);
  TTreeReaderValue<Double_t> edtm1_NOREF(readNOREF, EDTM_TRIG1_tdcTime);
  TTreeReaderValue<Double_t> edtm3_NOREF(readNOREF, EDTM_TRIG3_tdcTime);  
  TTreeReaderValue<Double_t> trig1Raw_NOREF(readNOREF, tdc_TRIG1_tdcTimeRaw);
  TTreeReaderValue<Double_t> trig3Raw_NOREF(readNOREF, tdc_TRIG3_tdcTimeRaw);
  TTreeReaderValue<Double_t> edtm1Raw_NOREF(readNOREF, EDTM_TRIG1_tdcTimeRaw);
  TTreeReaderValue<Double_t> edtm3Raw_NOREF(readNOREF, EDTM_TRIG3_tdcTimeRaw);

  TTreeReaderValue<Double_t> trig1_REF(readREF, tdc_TRIG1_tdcTime);
  TTreeReaderValue<Double_t> trig3_REF(readREF, tdc_TRIG3_tdcTime);
  TTreeReaderValue<Double_t> edtm1_REF(readREF, EDTM_TRIG1_tdcTime);
  TTreeReaderValue<Double_t> edtm3_REF(readREF, EDTM_TRIG3_tdcTime);  
  TTreeReaderValue<Double_t> trig1Raw_REF(readREF, tdc_TRIG1_tdcTimeRaw);
  TTreeReaderValue<Double_t> trig3Raw_REF(readREF, tdc_TRIG3_tdcTimeRaw);
  TTreeReaderValue<Double_t> edtm1Raw_REF(readREF, EDTM_TRIG1_tdcTimeRaw);
  TTreeReaderValue<Double_t> edtm3Raw_REF(readREF, EDTM_TRIG3_tdcTimeRaw);

  TTreeReaderValue<Double_t> H_S1X(tsh, "H.S1X.scaler");
  TTreeReaderValue<Double_t> H_S1Y(tsh, "H.S1Y.scaler");
  TTreeReaderValue<Double_t> H_S2X(tsh, "H.S2X.scaler");
  TTreeReaderValue<Double_t> H_S2Y(tsh, "H.S2Y.scaler");

  TTreeReaderValue<Double_t> P_S1X(tsp, "P.S1X.scaler");
  TTreeReaderValue<Double_t> P_S1Y(tsp, "P.S1Y.scaler");
  TTreeReaderValue<Double_t> P_S2X(tsp, "P.S2X.scaler");
  TTreeReaderValue<Double_t> P_S2Y(tsp, "P.S2Y.scaler");

  //Used for leave creation, just a copy of replay leaves
  Double_t noref,brtrig1_NOREF, brtrig3_NOREF, bredtm1_NOREF, bredtm3_NOREF, brtrig1Raw_NOREF, brtrig3Raw_NOREF, bredtm1Raw_NOREF, bredtm3Raw_NOREF;

  Double_t ref,brtrig1_REF, brtrig3_REF, bredtm1_REF, bredtm3_REF, brtrig1Raw_REF, brtrig3Raw_REF, bredtm1Raw_REF, bredtm3Raw_REF;

  Double_t brH_S1X, brH_S1Y, brH_S2X, brH_S2Y, brP_S1X, brP_S1Y, brP_S2X, brP_S2Y;

  Ttrig->Branch("T.coin.pTRIG1_ROC2_tdcTime[NO REF]", &brtrig1_NOREF,"brtrig1_NOREF/D");
  Ttrig->Branch("T.coin.pTRIG3_ROC1_tdcTime[NO REF]", &brtrig3_NOREF,"brtrig3_NOREF/D");
  Ttrig->Branch("T.coin.pTRIG1_ROC2_tdcTime[REF]", &brtrig1_REF,"brtrig1_REF/D");
  Ttrig->Branch("T.coin.pTRIG3_ROC1_tdcTime[REF]", &brtrig3_REF,"brtrig3_REF/D");
  Ttrig->Branch("T.coin.pTRIG1_ROC2_tdcTimeRaw[NO REF]", &brtrig1Raw_NOREF,"brtrig1Raw_NOREF/D");
  Ttrig->Branch("T.coin.pTRIG3_ROC1_tdcTimeRaw[NO REF]", &brtrig3Raw_NOREF,"brtrig3Raw_NOREF/D");
  Ttrig->Branch("T.coin.pTRIG1_ROC2_tdcTimeRaw[REF]", &brtrig1Raw_REF,"brtrig1Raw_REF/D");
  Ttrig->Branch("T.coin.pTRIG3_ROC1_tdcTimeRaw[REF]", &brtrig3Raw_REF,"brtrig3Raw_REF/D");

  Tedtm->Branch("T.coin.pEDTM_tdcTime[NO REF TRIG1]", &bredtm1_NOREF,"bredtm1_NOREF/D"); 
  Tedtm->Branch("T.coin.pEDTM_tdcTime[NO REF TRIG3]", &bredtm3_NOREF,"bredtm3_NOREF/D");
  Tedtm->Branch("T.coin.pEDTM_tdcTime[REF TRIG1]", &bredtm1_REF,"bredtm1_REF/D"); 
  Tedtm->Branch("T.coin.pEDTM_tdcTime[REF TRIG3]", &bredtm3_REF,"bredtm3_REF/D");
  Tedtm->Branch("T.coin.pEDTM_tdcTimeRaw[NO REF TRIG1]", &bredtm1Raw_NOREF,"bredtm1Raw_NOREF/D"); 
  Tedtm->Branch("T.coin.pEDTM_tdcTimeRaw[NO REF TRIG3]", &bredtm3Raw_NOREF,"bredtm3Raw_NOREF/D");
  Tedtm->Branch("T.coin.pEDTM_tdcTimeRaw[REF TRIG1]", &bredtm1Raw_REF,"bredtm1Raw_REF/D"); 
  Tedtm->Branch("T.coin.pEDTM_tdcTimeRaw[REF TRIG1]", &bredtm3Raw_REF,"bredtm3Raw_REF/D");

  Tscaler->Branch("H.S1X.scaler", &brH_S1X,"brH_S1X/D");
  Tscaler->Branch("H.S1Y.scaler", &brH_S1Y,"brH_S1Y/D");
  Tscaler->Branch("H.S2X.scaler", &brH_S2X,"brH_S2X/D");
  Tscaler->Branch("H.S2Y.scaler", &brH_S2Y,"brH_S2Y/D");

  Tscaler->Branch("P.S1X.scaler", &brP_S1X,"brP_S1X/D");
  Tscaler->Branch("P.S1Y.scaler", &brP_S1Y,"brP_S1Y/D");
  Tscaler->Branch("P.S2X.scaler", &brP_S2X,"brP_S2X/D");
  Tscaler->Branch("P.S2Y.scaler", &brP_S2Y,"brP_S2Y/D");

  Ttrig->SetBranchAddress("T.coin.pTRIG1_ROC2_tdcTime[NO REF]", &brtrig1_NOREF);
  Ttrig->SetBranchAddress("T.coin.pTRIG3_ROC1_tdcTime[NO REF]", &brtrig3_NOREF);
  Ttrig->SetBranchAddress("T.coin.pTRIG1_ROC2_tdcTime[REF]", &brtrig1_REF);
  Ttrig->SetBranchAddress("T.coin.pTRIG3_ROC1_tdcTime[REF]", &brtrig3_REF);
  Ttrig->SetBranchAddress("T.coin.pTRIG1_ROC2_tdcTimeRaw[NO REF]", &brtrig1Raw_NOREF);
  Ttrig->SetBranchAddress("T.coin.pTRIG3_ROC1_tdcTimeRaw[NO REF]", &brtrig3Raw_NOREF);
  Ttrig->SetBranchAddress("T.coin.pTRIG1_ROC2_tdcTimeRaw[REF]", &brtrig1Raw_REF);
  Ttrig->SetBranchAddress("T.coin.pTRIG3_ROC1_tdcTimeRaw[REF]", &brtrig3Raw_REF);

  Tedtm->SetBranchAddress("T.coin.pEDTM_tdcTime[NO REF TRIG1]", &bredtm1_NOREF); 
  Tedtm->SetBranchAddress("T.coin.pEDTM_tdcTime[NO REF TRIG3]", &bredtm3_NOREF);
  Tedtm->SetBranchAddress("T.coin.pEDTM_tdcTime[REF TRIG1]", &bredtm1_REF); 
  Tedtm->SetBranchAddress("T.coin.pEDTM_tdcTime[REF TRIG3]", &bredtm3_REF);
  Tedtm->SetBranchAddress("T.coin.pEDTM_tdcTimeRaw[NO REF TRIG1]", &bredtm1Raw_NOREF); 
  Tedtm->SetBranchAddress("T.coin.pEDTM_tdcTimeRaw[NO REF TRIG3]", &bredtm3Raw_NOREF);
  Tedtm->SetBranchAddress("T.coin.pEDTM_tdcTimeRaw[REF TRIG1]", &bredtm1Raw_REF); 
  Tedtm->SetBranchAddress("T.coin.pEDTM_tdcTimeRaw[REF TRIG1]", &bredtm3Raw_REF);

  Tscaler->SetBranchAddress("H.S1X.scaler", &brH_S1X);
  Tscaler->SetBranchAddress("H.S1Y.scaler", &brH_S1Y);
  Tscaler->SetBranchAddress("H.S2X.scaler", &brH_S2X);
  Tscaler->SetBranchAddress("H.S2Y.scaler", &brH_S2Y);

  Tscaler->SetBranchAddress("P.S1X.scaler", &brP_S1X);
  Tscaler->SetBranchAddress("P.S1Y.scaler", &brP_S1Y);
  Tscaler->SetBranchAddress("P.S2X.scaler", &brP_S2X);
  Tscaler->SetBranchAddress("P.S2Y.scaler", &brP_S2Y);

  while(readNOREF.Next()){

    //Leaves
    brtrig1_NOREF = *trig1_NOREF;
    brtrig3_NOREF = *trig3_NOREF;
    bredtm1_NOREF = *edtm1_NOREF;
    bredtm3_NOREF = *edtm3_NOREF;
    brtrig1Raw_NOREF = *trig1Raw_NOREF;
    brtrig3Raw_NOREF = *trig3Raw_NOREF;
    bredtm1Raw_NOREF = *edtm1Raw_NOREF;
    bredtm3Raw_NOREF = *edtm3Raw_NOREF;

    //Histograms
    htrig1_NOREF->Fill(*trig1_NOREF);
    htrig3_NOREF->Fill(*trig3_NOREF);
    hedtm1_NOREF->Fill(*edtm1_NOREF);
    hedtm3_NOREF->Fill(*edtm3_NOREF);
    htrig1Raw_NOREF->Fill(*trig1Raw_NOREF);
    htrig3Raw_NOREF->Fill(*trig3Raw_NOREF);
    hedtm1Raw_NOREF->Fill(*edtm1Raw_NOREF);
    hedtm3Raw_NOREF->Fill(*edtm3Raw_NOREF);

    trig1v3NOREF->GetXaxis()->SetTitle("SHMS pTrig 1 (ns)");
    trig1v3NOREF->GetYaxis()->SetTitle("HMS pTrig 3 (ns)");

    edtm1v3NOREF->GetXaxis()->SetTitle("SHMS pTrig 1 (ns)");
    edtm1v3NOREF->GetYaxis()->SetTitle("HMS pTrig 3 (ns)");
    
    trig1v3NOREF->Fill(*trig1_NOREF,*trig3_NOREF);
    edtm1v3NOREF->Fill(*edtm1_NOREF,*edtm3_NOREF);

    Ttrig->Fill();
    Tedtm->Fill();
  }

  while(readREF.Next()){

    //Leaves
    brtrig1_REF = *trig1_REF;
    brtrig3_REF = *trig3_REF;
    bredtm1_REF = *edtm1_REF;
    bredtm3_REF = *edtm3_REF;
    brtrig1Raw_REF = *trig1Raw_REF;
    brtrig3Raw_REF = *trig3Raw_REF;
    bredtm1Raw_REF = *edtm1Raw_REF;
    bredtm3Raw_REF = *edtm3Raw_REF;

    // brH_S1X = *H_S1X;
    // brH_S1Y = *H_S1Y;
    // brH_S2X = *H_S2X;
    // brH_S2Y = *H_S2Y;

    // brP_S1X = *P_S1X;
    // brP_S1Y = *P_S1Y;
    // brP_S2X = *P_S2X;
    // brP_S2Y = *P_S2Y;
    
    // if(((*trig1_REF >= 214 && *trig1_REF <= 219) || (*trig1_REF >= 391 && *trig1_REF <= 394)) &&
    //    (*trig3_REF >= 289 && *trig3_REF <= 293)
    if((*trig1_REF >= 215 && *trig1_REF <= 225) &&
       (*trig3_REF >= 415 && *trig3_REF <= 425)   
       //&& (*H_S1X != 0 && *H_S1Y != 0 && *H_S2X != 0 && *H_S2Y != 0)
       //&& (*P_S1X != 0 && *P_S1Y != 0 && *P_S2X != 0 && *P_S2Y != 0)
       ){
         
      //Histograms
      htrig1_REF->Fill(*trig1_REF);
      htrig3_REF->Fill(*trig3_REF);
      htrig1Raw_REF->Fill(*trig1Raw_REF);
      htrig3Raw_REF->Fill(*trig3Raw_REF);

      trig1v3REF->GetXaxis()->SetTitle("SHMS pTrig 1 (ns)");
      trig1v3REF->GetYaxis()->SetTitle("HMS pTrig 3 (ns)");
      
      trig1v3REF->Fill(*trig1_REF,*trig3_REF);
      
    }

    trig1v3REF_NOCUT->GetXaxis()->SetTitle("SHMS pTrig 1 (ns)");
    trig1v3REF_NOCUT->GetYaxis()->SetTitle("HMS pTrig 3 (ns)");
    
    trig1v3REF_NOCUT->Fill(*trig1_REF,*trig3_REF);
    
    if((*edtm3_REF >= 141 && *edtm3_REF <= 143) || (*edtm1_REF >= 141 && *edtm1_REF <= 143)
       ){

      //Histograms
      hedtm1_REF->Fill(*edtm1_REF);
      hedtm3_REF->Fill(*edtm3_REF);
      hedtm1Raw_REF->Fill(*edtm1Raw_REF);
      hedtm3Raw_REF->Fill(*edtm3Raw_REF);

      edtm1v3REF->GetXaxis()->SetTitle("SHMS pTrig 1 (ns)");
      edtm1v3REF->GetYaxis()->SetTitle("HMS pTrig 3 (ns)");
      
      edtm1v3REF->Fill(*edtm1_REF,*edtm3_REF);
      
    }

    edtm1v3REF_NOCUT->GetXaxis()->SetTitle("SHMS pTrig 1 (ns)");
    edtm1v3REF_NOCUT->GetYaxis()->SetTitle("HMS pTrig 3 (ns)");

    edtm1v3REF_NOCUT->Fill(*edtm1_REF,*edtm3_REF);

    // if((((*trig1_REF >= 214 && *trig1_REF <= 219) || (*trig1_REF >= 391 && *trig1_REF <= 394)) &&
    // 	(*trig3_REF >= 289 && *trig3_REF <= 293)) &&
    if((*trig1_REF >= 215 && *trig1_REF <= 225) &&
       (*trig3_REF >= 415 && *trig3_REF <= 425) &&
       ((*edtm3_REF >= 141 && *edtm3_REF <= 143) || (*edtm1_REF >= 141 && *edtm1_REF <= 143))
       //&& (*H_S1X != 0 && *H_S1Y != 0 && *H_S2X != 0 && *H_S2Y != 0)
       //&& (*P_S1X != 0 && *P_S1Y != 0 && *P_S2X != 0 && *P_S2Y != 0)
       ){

      trig1v3REF_EDTMCUT->GetXaxis()->SetTitle("SHMS pTrig 1 (ns)");
      trig1v3REF_EDTMCUT->GetYaxis()->SetTitle("HMS pTrig 3 (ns)");

      trig1v3REF_EDTMCUT->Fill(*trig1_REF,*trig3_REF);
      
    }
    
    Ttrig->Fill();
    Tedtm->Fill();
    Tscaler->Fill();
  }

  f1->Close();
  f2->Close();

  ////////////////////////////////////////////////////////////////
  // Below are the histograms to see cuts applied to TDC leaves //
  ////////////////////////////////////////////////////////////////
  htrig1_NOREF->SetLineColor(2);
  htrig1_NOREF->SetFillColor(42);

  ctdcTime1->cd();
  htrig1_NOREF->Draw();
  htrig1_REF->Draw("SAME");
  ctdcTime1->Modified(); ctdcTime1->Update();
  ctdcTime1-> SetLogy();
  ctdcTime1->Draw();

  ////////////////////////////////////////////////////////////////
  htrig1Raw_NOREF->SetLineColor(2);
  htrig1Raw_NOREF->SetFillColor(42);

  ctdcTime1Raw->cd();
  htrig1Raw_NOREF->Draw();
  htrig1Raw_REF->Draw("SAME");
  ctdcTime1Raw->Modified(); ctdcTime1Raw->Update();
  ctdcTime1Raw-> SetLogy();
  ctdcTime1Raw->Draw();

  ////////////////////////////////////////////////////////////////
  htrig3_NOREF->SetLineColor(2);
  htrig3_NOREF->SetFillColor(42);
  
  ctdcTime3->cd();
  htrig3_NOREF->Draw();
  htrig3_REF->Draw("SAME");
  ctdcTime3->Modified(); ctdcTime3->Update();
  ctdcTime3-> SetLogy();
  ctdcTime3->Draw();

  ////////////////////////////////////////////////////////////////
  htrig3Raw_NOREF->SetLineColor(2);
  htrig3Raw_NOREF->SetFillColor(42);

  ctdcTime3Raw->cd();
  htrig3Raw_NOREF->Draw();
  htrig3Raw_REF->Draw("SAME");
  ctdcTime3Raw->Modified(); ctdcTime3Raw->Update();
  ctdcTime3Raw-> SetLogy();
  ctdcTime3Raw->Draw();

  ////////////////////////////////////////////////////////////////
  hedtm1_NOREF->SetLineColor(2);
  hedtm1_NOREF->SetFillColor(42);

  cedtm1->cd();
  hedtm1_NOREF->Draw();
  hedtm1_REF->Draw("SAME");
  cedtm1->Modified(); cedtm1->Update();
  cedtm1-> SetLogy();
  cedtm1->Draw();

  ////////////////////////////////////////////////////////////////
  hedtm1Raw_NOREF->SetLineColor(2);
  hedtm1Raw_NOREF->SetFillColor(42);
  
  cedtm1Raw->cd();
  hedtm1Raw_NOREF->Draw();
  hedtm1Raw_REF->Draw("SAME");
  cedtm1Raw->Modified(); cedtm1Raw->Update();
  cedtm1Raw-> SetLogy();
  cedtm1Raw->Draw();

  ////////////////////////////////////////////////////////////////
  hedtm3_NOREF->SetLineColor(2);
  hedtm3_NOREF->SetFillColor(42);
  
  cedtm3->cd();
  hedtm3_NOREF->Draw();
  hedtm3_REF->Draw("SAME");
  cedtm3->Modified(); cedtm3->Update();
  cedtm3-> SetLogy();
  cedtm3->Draw();

  ////////////////////////////////////////////////////////////////
  hedtm3Raw_NOREF->SetLineColor(2);
  hedtm3Raw_NOREF->SetFillColor(42);
  
  cedtm3Raw->cd();
  hedtm3Raw_NOREF->Draw();
  hedtm3Raw_REF->Draw("SAME");
  cedtm3Raw->Modified(); cedtm3Raw->Update();
  cedtm3Raw-> SetLogy();
  cedtm3Raw->Draw();
  
  Ttrig->Print();
  Tedtm->Print();
  Tscaler->Print();
  out->Print();
  
  out->Append(ctdcTime1);
  out->Append(ctdcTime3);
  out->Append(ctdcTime1Raw);
  out->Append(ctdcTime3Raw);
  out->Append(cedtm1);
  out->Append(cedtm3);
  out->Append(cedtm1Raw);
  out->Append(cedtm3Raw);

  out->Write();  
}
