#include <TFile.h>
#include <TH1.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

void analysis_heep_offset(TString eInput = "", TString runNum = ""){
//Making 1D histograms overlayed of two input files- finding kaons in kaon experiment.
//This is the first set of data we will be taking; Q2 of 0.4 GeV2 and W of 2.45 Gev 

  TString spec = "hms";
  
  cout << "\nThis will be run for " << spec << "\n\n";
  
  if (eInput=="") {
  cout << "Please enter energy...\n";
  cin >> eInput;
  }
  
  if (runNum=="") {
  cout << "Please enter run number...\n";
  cin >> runNum;
  }

  TString rootfile1 = "heep_" + spec +"_" + eInput + "_" + runNum;
  TString rootfile2 = "heep_" + spec +"_" + eInput + "_" + runNum + "_offset";
  TString outputhist1;
  TString outputhist2;
  outputhist1 = "~/ResearchNP/simulations_p-k/simc_gfortran/worksim/" + rootfile1 + ".root";
  outputhist2 = "~/ResearchNP/simulations_p-k/simc_gfortran/worksim/" + rootfile2 + ".root";
  TString outputpdf;
  outputpdf = "OUTPUT/" + rootfile2 + ".pdf";

  TFile *f1 = TFile::Open(outputhist1);
  TFile *f2 = TFile::Open(outputhist2);
  if( !f1 || f1->IsZombie() ||  !f2 || f2->IsZombie()){
	return;
  }
  
  ////////////////////////////////////////////////////////
  
  TTreeReader r1("h666", f1);

  TTreeReader r1a("h666", f2);

  TTreeReaderValue<Float_t> hsdelta1(r1, "hsdelta");
  TTreeReaderValue<Float_t> ssdelta1(r1, "ssdelta");
  TTreeReaderValue<Float_t> hsxptar1(r1, "hsxptar");
  TTreeReaderValue<Float_t> hsyptar1(r1, "hsyptar");
  TTreeReaderValue<Float_t> ssyptar1(r1, "ssyptar");
  TTreeReaderValue<Float_t> ssxptar1(r1, "ssxptar");
  TTreeReaderValue<Float_t> weight1(r1, "Weight");

  TTreeReaderValue<Float_t> hsdelta1a(r1a, "hsdelta");
  TTreeReaderValue<Float_t> ssdelta1a(r1a, "ssdelta");
  TTreeReaderValue<Float_t> hsxptar1a(r1a, "hsxptar");
  TTreeReaderValue<Float_t> hsyptar1a(r1a, "hsyptar");
  TTreeReaderValue<Float_t> ssyptar1a(r1a, "ssyptar");
  TTreeReaderValue<Float_t> ssxptar1a(r1a, "ssxptar");
  TTreeReaderValue<Float_t> weight1a(r1a, "Weight");

  TCanvas *c1 = new TCanvas("c1","hsdelta", 600, 400); 
  TH1F *h1 = new TH1F("h1","hsdelta", 200, -22, 25);
  TH1F *h1a = new TH1F("h1a","hsdelta", 200, -22, 25);

  while(r1.Next()){
       int i;
        cout << "~While loop hsdelta " << i << '\n';      

	if(*hsdelta1 > -8 && *hsdelta1 < 8
		&& *ssdelta1 > -10 && *ssdelta1 < 15
		//&& *hsxptar1 > -0.065 && *hsxptar1 < 0.05
		//&& *hsyptar1 > -0.02 && *hsyptar1 < 0.025
		//&& *ssyptar1 > -0.03 && *ssyptar1 < 0.025
		//&& *ssxptar1 > -0.04 && *ssxptar1 < 0.04
		){
        h1->Fill(*hsdelta1, *weight1); 
	i++;
	}	

  }

  while(r1a.Next()){
       int i;
        cout << "~While loop hsdelta " << i << '\n';      

	if(*hsdelta1a > -8 && *hsdelta1a < 8
		&& *ssdelta1a > -10 && *ssdelta1a < 15
		//&& *hsxptar1a > -0.065 && *hsxptar1a < 0.05
		//&& *hsyptar1a > -0.02 && *hsyptar1a < 0.025
		//&& *ssyptar1a > -0.03 && *ssyptar1a < 0.025
		//&& *ssxptar1a > -0.04 && *ssxptar1a < 0.04
		){
        h1a->Fill(*hsdelta1a, *weight1a); 
	i++;
	}	

  }

  h1->Draw(); 
  h1a->SetLineColor(kRed);
  h1a->Draw("SAME"); 
/*
  TString integral1;
  integral1.Form("%f1",h1->Integral());
  h1->GetXaxis()->SetTitle("Integrated Value:" + integral1);
  cout << integral1 << " ";

  TString integral1a;
  integral1a.Form("%f1",h1a->Integral());
  h1a->GetXaxis()->SetTitle("Integrated Value:" + integral1a);
  cout << integral1a << " ";
*/
  c1->Print(outputpdf + "(");
  //c1->Print("OUTPUT/" + rootfile + "_hsdelta" + ".png");

////////////////////////////////////////////////////////

  TTreeReader r2("h666", f1);

  TTreeReaderValue<Float_t> hsdelta2(r2, "hsdelta");
  TTreeReaderValue<Float_t> ssdelta2(r2, "ssdelta");
  TTreeReaderValue<Float_t> hsxptar2(r2, "hsxptar");
  TTreeReaderValue<Float_t> hsyptar2(r2, "hsyptar");
  TTreeReaderValue<Float_t> ssyptar2(r2, "ssyptar");
  TTreeReaderValue<Float_t> ssxptar2(r2, "ssxptar");
  TTreeReaderValue<Float_t> weight2(r2, "Weight");

  TCanvas *c2 = new TCanvas("c2","ssdelta", 600, 400); 
  TH1F *h2 = new TH1F("h2","ssdelta", 200, -22, 25);

  while(r2.Next()){
	int k;
        cout << "While loop ssdelta " << k << '\n'; 

	if(*hsdelta2 > -8 && *hsdelta2 < 8
		&& *ssdelta2 > -10 && *ssdelta2 < 15
		//&& *hsxptar2 > -0.065 && *hsxptar2 < 0.05
		//&& *hsyptar2 > -0.02 && *hsyptar2 < 0.025
		//&& *ssyptar2 > -0.03 && *ssyptar2 < 0.025
		//&& *ssxptar2 > -0.04 && *ssxptar2 < 0.04)
		){
	h2->Fill(*ssdelta2, *weight2);     
        k++;
	}

  }

  h2->Draw();

  TString integral2;
  integral2.Form("%f1",h2->Integral());
  h2->GetXaxis()->SetTitle("Integrated Value:" + integral2);
  cout << integral2 << " ";

  c2->Print(outputpdf);
  //c2->Print("OUTPUT/" + rootfile + "_ssdelta" + ".png");

////////////////////////////////////////////////////////

  TTreeReader r3("h666", f1);

  TTreeReaderValue<Float_t> hsdelta3(r3, "hsdelta");
  TTreeReaderValue<Float_t> ssdelta3(r3, "ssdelta");
  TTreeReaderValue<Float_t> hsxptar3(r3, "hsxptar");
  TTreeReaderValue<Float_t> hsyptar3(r3, "hsyptar");
  TTreeReaderValue<Float_t> ssyptar3(r3, "ssyptar");
  TTreeReaderValue<Float_t> ssxptar3(r3, "ssxptar");
  TTreeReaderValue<Float_t> weight3(r3, "Weight");

  TCanvas *c3 = new TCanvas("c3","hsxptar", 600, 400); 
  TH1F *h3 = new TH1F("h3","hsxptar", 200, -0.2, 0.2);

  while(r3.Next()){
       int j;
        cout << "~While loop hsxptar " << j << '\n';

	if(*hsdelta3 > -8 && *hsdelta3 < 8
		&& *ssdelta3 > -10 && *ssdelta3 < 15
		//&& *hsxptar3 > -0.065 && *hsxptar3 < 0.05
		//&& *hsyptar3 > -0.02 && *hsyptar3 < 0.025
		//&& *ssyptar3 > -0.03 && *ssyptar3 < 0.025
		//&& *ssxptar3 > -0.04 && *ssxptar3 < 0.04)
		){
        h3->Fill(*hsxptar3, *weight3); 
	j++;
	}

  }

  h3->Draw();

  TString integral3;
  integral3.Form("%f1",h3->Integral());
  h3->GetXaxis()->SetTitle("Integrated Value:" + integral3);
  cout << integral3 << " ";

  c3->Print(outputpdf);
  //c3->Print("OUTPUT/" + rootfile + "_hsxptar" + ".png");

////////////////////////////////////////////////////////

  TTreeReader r4("h666", f1);

  TTreeReaderValue<Float_t> hsdelta4(r4, "hsdelta");
  TTreeReaderValue<Float_t> ssdelta4(r4, "ssdelta");
  TTreeReaderValue<Float_t> hsxptar4(r4, "hsxptar");
  TTreeReaderValue<Float_t> hsyptar4(r4, "hsyptar");
  TTreeReaderValue<Float_t> ssyptar4(r4, "ssyptar");
  TTreeReaderValue<Float_t> ssxptar4(r4, "ssxptar");
  TTreeReaderValue<Float_t> weight4(r4, "Weight");

  TCanvas *c4 = new TCanvas("c4","hsyptar", 600, 400); 
  TH1F *h4 = new TH1F("h4","hsyptar", 200, -0.2, 0.2);

  while(r4.Next()){
       int j;
        cout << "~While loop hsyptar " << j << '\n';

	if(*hsdelta4 > -8 && *hsdelta4 < 8
		&& *ssdelta4 > -10 && *ssdelta4 < 15
		//&& *hsxptar4 > -0.065 && *hsxptar4 < 0.05
		//&& *hsyptar4 > -0.02 && *hsyptar4 < 0.025
		//&& *ssyptar4 > -0.03 && *ssyptar4 < 0.025
		//&& *ssxptar4 > -0.04 && *ssxptar4 < 0.04)
		){
        h4->Fill(*hsyptar4, *weight4); 
	j++;
	}

  }

  h4->Draw();

  TString integral4;
  integral4.Form("%f1",h4->Integral());
  h4->GetXaxis()->SetTitle("Integrated Value:" + integral4);
  cout << integral4 << " ";

  c4->Print(outputpdf);
  //c4->Print("OUTPUT/" + rootfile + "_hsyptar" + ".png");

////////////////////////////////////////////////////////

  TTreeReader r5("h666", f1);

  TTreeReaderValue<Float_t> hsdelta5(r5, "hsdelta");
  TTreeReaderValue<Float_t> ssdelta5(r5, "ssdelta");
  TTreeReaderValue<Float_t> hsxptar5(r5, "hsxptar");
  TTreeReaderValue<Float_t> hsyptar5(r5, "hsyptar");
  TTreeReaderValue<Float_t> ssyptar5(r5, "ssyptar");
  TTreeReaderValue<Float_t> ssxptar5(r5, "ssxptar");
  TTreeReaderValue<Float_t> weight5(r5, "Weight");

  TCanvas *c5 = new TCanvas("c5","ssyptar", 600, 400); 
  TH1F *h5 = new TH1F("h5","ssyptar", 200, -0.2, 0.2);

  while(r5.Next()){
       int j;
        cout << "~While loop ssyptar " << j << '\n';

	if(*hsdelta5 > -8 && *hsdelta5 < 8
		&& *ssdelta5 > -10 && *ssdelta5 < 15
		//&& *hsxptar5 > -0.065 && *hsxptar5 < 0.05
		//&& *hsyptar5 > -0.02 && *hsyptar5 < 0.025
		//&& *ssyptar5 > -0.03 && *ssyptar5 < 0.025
		//&& *ssxptar5 > -0.04 && *ssxptar5 < 0.04)
		){
        h5->Fill(*ssyptar5, *weight5); 
	j++;
		}

  }

  h5->Draw();

  TString integral5;
  integral5.Form("%f1",h5->Integral(0,2));
  h5->GetXaxis()->SetTitle("Integrated Value:" + integral5);
  cout << integral5 << " ";

  c5->Print(outputpdf);
  //c5->Print("OUTPUT/" + rootfile + "_ssyptar" + ".png");

////////////////////////////////////////////////////////

  TTreeReader r6("h666", f1);

  TTreeReaderValue<Float_t> hsdelta6(r6, "hsdelta");
  TTreeReaderValue<Float_t> ssdelta6(r6, "ssdelta");
  TTreeReaderValue<Float_t> hsxptar6(r6, "hsxptar");
  TTreeReaderValue<Float_t> hsyptar6(r6, "hsyptar");
  TTreeReaderValue<Float_t> ssyptar6(r6, "ssyptar");
  TTreeReaderValue<Float_t> ssxptar6(r6, "ssxptar");
  TTreeReaderValue<Float_t> weight6(r6, "Weight");

  TCanvas *c6 = new TCanvas("c6","ssxptar", 600, 400); 
  TH1F *h6 = new TH1F("h6","ssxptar", 200, -0.2, 0.2);

  while(r6.Next()){
       int j;
        cout << "~While loop ssxptar " << j << '\n';

	if(*hsdelta6 > -8 && *hsdelta6 < 8
		&& *ssdelta6 > -10 && *ssdelta6 < 15
		//&& *hsxptar6 > -0.065 && *hsxptar6 < 0.05
		//&& *hsyptar6 > -0.02 && *hsyptar6 < 0.025
		//&& *ssyptar6 > -0.03 && *ssyptar6 < 0.025
		//&& *ssxptar6 > -0.04 && *ssxptar6 < 0.04)
		){
        h6->Fill(*ssxptar6, *weight6); 
	j++;
		}

  }

  h6->Draw();

  TString integral6;
  integral6.Form("%f1",h6->Integral());
  h6->GetXaxis()->SetTitle("Integrated Value:" + integral6);
  cout << integral6 << " ";

  c6->Print(outputpdf + ")");
  //c6->Print("OUTPUT/" + rootfile + "_ssxptar" + ".png");

////////////////////////////////////////////////////////
/*
  TTreeReader r7("h666", f1);

  TTreeReaderValue<Float_t> weight7(r7, "Weight");
  TTreeReaderValue<Float_t> em(r7, "Em");
  TTreeReaderValue<Float_t> pm(r7, "Pm");

  TCanvas *c7 = new TCanvas("c7","missmass", 600, 400); 
  TH1F *h7 = new TH1F("h7","missmass", 200, -0.2, 0.2);

  while(r7.Next()){
       int j;
        cout << "~While loop missmass " << j << '\n';

	if(*missmass < 1.15){
        h7->Fill(*missmass, *weight7); 
	j++;
		}

  }

  h7->Draw();

  TString integral7;
  integral7.Form("%f1",h7->Integral(0,2));
  h7->GetXaxis()->SetTitle("Integrated Value:" + integral7);
  cout << integral7 << " ";

  c7->Print(outputpdf + ")");
  //c7->Print(rootfile + "_missmass" + ".png");
  */
  ////////////////////////////////////////////////////////
  /*
  TTreeReader r8("h666", f1);

  TTreeReaderValue<Float_t> weight8(r8, "Weight");
  TTreeReaderValue<Float_t> missmass2(r8, "Em");
  TTreeReaderValue<Float_t> ssxptar2(r8, "ssxptar");

  TCanvas *c8 = new TCanvas("c8","missmass", 600, 400); 
  TH2F *h8 = new TH2F("h8","missmass", 200, -0.2, 0.2, 200, -0.2, 0.2);

  while(r8.Next()){
       int j;
        cout << "~While loop missmass " << j << '\n';

	//if(*missmass < 1.15){
        h8->Fill(*missmass2, *ssxptar2, *weight8); 
	j++;
		//}

  }

  h8->Draw();

  TString integral8;
  integral8.Form("%f",h8->Integral());
  h8->GetXaxis()->SetTitle("Integrated Value:" + integral8);
  cout << integral8 << " ";

  //c8->Print(outputpdf + ")");
  c8->Print("OUTPUT/" + rootfile + "_missmass_xptar" + ".png");
  */
  
  
  return;
    }
