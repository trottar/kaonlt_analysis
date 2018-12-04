#include <string>
#include <cstdio>
#include <iostream>

void plot_Stat(Int_t runNum = 0, Int_t numEvts = 0, TString spec = ""){

  if(runNum==0){
  
  	cout << "Please enter run number ...\n";
  	cin >> runNum;
  }
  
  if(numEvts==0){
  
  	cout << "Please enter number of events in replay ...\n";
  	cin >> numEvts;
  }

  if(spec==""){
  
  	cout << "Please pick a spectrometer ...\n";
  	cin >> spec;
  }

  TString rootfile = "../../ROOTfiles/KaonLT_" + spec + Form("_coin_replay_production_%i_%i",runNum,numEvts);

  TString outputhist;
  outputhist = rootfile + ".root";
  
  TString outputpdf;
  outputpdf = "OUTPUT/" + spec + "_statsPlots_" + Form("%i",runNum) + ".pdf";
  
  TFile *f = TFile::Open(outputhist);
  if( !f || f->IsZombie()){
	return;
  }
  
  TString xfpLeaf, yfpLeaf, deltaLeaf,xptarLeaf, yptarLeaf, wLeaf;
  
  TTreeReader r("T", f);

  TCanvas *c1 = new TCanvas("c1","Stat plots", 600, 400); 
  TCanvas *c2 = new TCanvas("c2","Stat plots", 600, 400);
  //TCanvas *c3 = new TCanvas("c3","Stat plots", 600, 400);
  //TCanvas *c4 = new TCanvas("c4","Stat plots", 600, 400);
  TH2F *h1 = new TH2F("h1","Xfp vs Yfp", 200,-50, 50,200,-50, 50);
  TH2F *h2= new TH2F("h2","Xptar vs Yptar", 200, -0.1, 0.1,200,-0.1, 0.1);
  //TH2F *h3= new TH2F("h3","W^2 vs Xptar ", 200, -.1, .1,200,0, 20);
  //TH2F *h4= new TH2F("h4","W^2 vs Yptar ", 200, -.1, .1,200,0, 20);
  
  if(spec == "hms"){
    xfpLeaf = "H.dc.x_fp";
    yfpLeaf = "H.dc.y_fp";
    xptarLeaf = "H.gtr.th";
    yptarLeaf = "H.gtr.ph";
    deltaLeaf = "H.gtr.dp";
    wLeaf = "H.kin.W2";
  TTreeReaderValue<Double_t> xfp(r, xfpLeaf);
  TTreeReaderValue<Double_t> yfp(r, yfpLeaf);
  TTreeReaderValue<Double_t> xptar(r, xptarLeaf);
  TTreeReaderValue<Double_t> yptar(r, yptarLeaf);
  TTreeReaderValue<Double_t> invmass(r, wLeaf);
  TTreeReaderValue<Double_t> hsdelta(r,deltaLeaf);
    while(r.Next()){
      
      int k;
      cout << "While loop W^2 " << k << '\n';
      
      if(*hsdelta > -8 && *hsdelta < 8
	 ){
	
	h1->Fill(*yfp,*xfp);
	h2->Fill(*yptar,*xptar);
	//h3->Fill(*xptar,*invmass);
	//h4->Fill(*yptar,*invmass);
	
	k++;
      }
      
    }
  h1->GetXaxis()->SetTitle("yfp");
  h1->GetYaxis()->SetTitle("xfp");

  h2->GetXaxis()->SetTitle("yptar");
  h2->GetYaxis()->SetTitle("xptar");

  //h3->GetYaxis()->SetTitle("W^2");
  //h3->GetXaxis()->SetTitle("xptar");

  //h4->GetYaxis()->SetTitle("W^2");
  //h4->GetXaxis()->SetTitle("yptar");

  //c1->Divide(2,2);
  //c1->cd(1);  
  h1->Draw("Colz");
  c1->Print(outputpdf+"(");
  //c1->cd(2);
  h2->Draw("Colz");
  c2->Print(outputpdf+ ")");
  //c1->cd(3);
  //h3->Draw("Colz");
  //c3->Print(outputpdf);
  //c1->cd(4);
  //h4->Draw("Colz");
  //c4->Print(outputpdf+")");

  //c1->Print("OUTPUT/pngFiles" + spec + "_statsPlots_" + Form("%i",(int)runNum) + ".png");

  const string sep = " |";
  const int total_width = 154;
  const string line = sep+ string(total_width-1,'-') + '|';

  ofstream myfile;
  }  

if(spec=="shms"){
    xfpLeaf = "P.dc.x_fp";
    yfpLeaf = "P.dc.y_fp";
    xptarLeaf = "P.gtr.th";
    yptarLeaf = "P.gtr.ph";
    deltaLeaf = "P.gtr.dp";
  TTreeReaderValue<Double_t> xfp(r, xfpLeaf);
  TTreeReaderValue<Double_t> yfp(r, yfpLeaf);
  TTreeReaderValue<Double_t> xptar(r, xptarLeaf);
  TTreeReaderValue<Double_t> yptar(r, yptarLeaf);
  TTreeReaderValue<Double_t> invmass(r, wLeaf);
  TTreeReaderValue<Double_t> ssdelta(r,deltaLeaf);
    while(r.Next()){
      
      int k;
      cout << "While loop W^2 " << k << '\n';
      
      if(*ssdelta > -10 && *ssdelta < 15
	 ){
	
	h1->Fill(*yfp,*xfp);
	h2->Fill(*yptar,*xptar);
	
	k++;
      }
      
    }
  h1->GetXaxis()->SetTitle("yfp");
  h1->GetYaxis()->SetTitle("xfp");

  h2->GetXaxis()->SetTitle("yptar");
  h2->GetYaxis()->SetTitle("xptar");

  //h3->GetYaxis()->SetTitle("W^2");
  //h3->GetXaxis()->SetTitle("xptar");

  //h4->GetYaxis()->SetTitle("W^2");
  //h4->GetXaxis()->SetTitle("yptar");

  //c1->Divide(2,2);
  //c1->cd(1);  
  h1->Draw("Colz");
  c1->Print(outputpdf+"(");
  //c1->cd(2);
  h2->Draw("Colz");
  c2->Print(outputpdf+ ")");
  //c1->cd(3);
  //h3->Draw("Colz");
  //c3->Print(outputpdf);
  //c1->cd(4);
  //h4->Draw("Colz");
  //c4->Print(outputpdf+")");

  //c1->Print("OUTPUT/pngFiles" + spec + "_statsPlots_" + Form("%i",(int)runNum) + ".png");

  const string sep = " |";
  const int total_width = 154;
  const string line = sep+ string(total_width-1,'-') + '|';

  ofstream myfile;
  }



}
