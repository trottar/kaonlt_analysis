#include <TFile.h>
#include <TH1.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

void analysis_kinematics(TString rootfile = ""){
//Making 1D histograms overlayed of two input files- finding kaons in kaon experiment.
//This is the first set of data we will be taking; Q2 of 0.4 GeV2 and W of 2.45 Gev 
  
  if (rootfile=="") {
  cout << "Please enter root name...\n";
  cin >> rootfile;
  }

  TString outputhist;
  outputhist = "../../ROOTfiles" + rootfile + ".root";
  TString outputpdf;
  outputpdf = "OUTPUT/" + rootfile + ".pdf";

  TFile *f = TFile::Open(outputhist);
  if( !f || f->IsZombie()){
	return;
  }
  
  TTreeReader r1("h666", f);

  TTreeReaderValue<Float_t> w2(r1, "H.kin.W2");
  //TTreeReaderValue<Float_t> weight1(r1, "evNumber");
  TTreeReaderValue<Float_t> scatAng(r1, "H.kin.scat_ang_deg");

  TCanvas *c1 = new TCanvas("c1","w2", 600, 400); 
  TH2F *h1 = new TH2F("h1","w2", 200, 0, 2500, 200, 0, 2500);

  while(r1.Next()){
       int i;
        cout << "~While loop w2 " << i << '\n';      
	
	//if(*w2 > -8 && *w2 < 8){
        h1->Fill(*w2, *scatAng, *weight1); 
	i++;
	//}

  }

  h1->Draw(); 

  TString integral1;
  integral1.Form("%f",h1->Integral());
  h1->GetXaxis()->SetTitle("Integrated Value:" + integral1);
  cout << integral1 << " ";

  //c1->Print(outputpdf + "(");
  c1->Print("OUTPUT/" + rootfile + "_w2" + ".png");

////////////////////////////////////////////////////////
/*
  TTreeReader r2("h666", f);

  TTreeReaderValue<Float_t> ssdelta(r2, "ssdelta");
  TTreeReaderValue<Float_t> weight2(r2, "Weight");

  TCanvas *c2 = new TCanvas("c2","ssdelta", 600, 400); 
  TH1F *h2 = new TH1F("h2","ssdelta", 200, -22, 25);

  while(r2.Next()){
	int k;
        cout << "While loop ssdelta " << k << '\n'; 

	if(*ssdelta > -15 && *ssdelta < 20){
	h2->Fill(*ssdelta, *weight2);     
        k++;
	}

  }

  h2->Draw();

  TString integral2;
  integral2.Form("%f",h2->Integral());
  h2->GetXaxis()->SetTitle("Integrated Value:" + integral2);
  cout << integral2 << " ";

  c2->Print(outputpdf);
  //c2->Print("OUTPUT/" + rootfile + "_ssdelta" + ".png");

////////////////////////////////////////////////////////

  TTreeReader r3("h666", f);

  TTreeReaderValue<Float_t> weight3(r3, "Weight");
  TTreeReaderValue<Float_t> hsxptar(r3, "hsxptar");

  TCanvas *c3 = new TCanvas("c3","hsxptar", 600, 400); 
  TH1F *h3 = new TH1F("h3","hsxptar", 200, -0.2, 0.2);

  while(r3.Next()){
       int j;
        cout << "~While loop hsxptar " << j << '\n';

	if(*hsxptar > -0.065 && *hsxptar < 0.05){
        h3->Fill(*hsxptar, *weight3); 
	j++;
	}

  }

  h3->Draw();

  TString integral3;
  integral3.Form("%f",h3->Integral());
  h3->GetXaxis()->SetTitle("Integrated Value:" + integral3);
  cout << integral3 << " ";

  c3->Print(outputpdf);
  //c3->Print("OUTPUT/" + rootfile + "_hsxptar" + ".png");

////////////////////////////////////////////////////////

  TTreeReader r4("h666", f);

  TTreeReaderValue<Float_t> weight4(r4, "Weight");
  TTreeReaderValue<Float_t> hsyptar(r4, "hsyptar");

  TCanvas *c4 = new TCanvas("c4","hsyptar", 600, 400); 
  TH1F *h4 = new TH1F("h4","hsyptar", 200, -0.2, 0.2);

  while(r4.Next()){
       int j;
        cout << "~While loop hsyptar " << j << '\n';

	if(*hsyptar > -0.02 && *hsyptar < 0.025){
        h4->Fill(*hsyptar, *weight4); 
	j++;
	}

  }

  h4->Draw();

  TString integral4;
  integral4.Form("%f",h4->Integral());
  h4->GetXaxis()->SetTitle("Integrated Value:" + integral4);
  cout << integral4 << " ";

  c4->Print(outputpdf);
  //c4->Print("OUTPUT/" + rootfile + "_hsyptar" + ".png");

////////////////////////////////////////////////////////

  TTreeReader r5("h666", f);

  TTreeReaderValue<Float_t> weight5(r5, "Weight");
  TTreeReaderValue<Float_t> ssyptar(r5, "ssyptar");

  TCanvas *c5 = new TCanvas("c5","ssyptar", 600, 400); 
  TH1F *h5 = new TH1F("h5","ssyptar", 200, -0.2, 0.2);

  while(r5.Next()){
       int j;
        cout << "~While loop ssyptar " << j << '\n';

	//if(*ssyptar > -0.03 && *ssyptar < 0.025){
        h5->Fill(*ssyptar, *weight5); 
	j++;
	//	}

  }

  h5->Draw();

  TString integral5;
  integral5.Form("%f",h5->Integral());
  h5->GetXaxis()->SetTitle("Integrated Value:" + integral5);
  cout << integral5 << " ";

  c5->Print(outputpdf);
  //c5->Print("OUTPUT/" + rootfile + "_ssyptar" + ".png");

////////////////////////////////////////////////////////

  TTreeReader r6("h666", f);

  TTreeReaderValue<Float_t> weight6(r6, "Weight");
  TTreeReaderValue<Float_t> ssxptar(r6, "ssxptar");

  TCanvas *c6 = new TCanvas("c6","ssxptar", 600, 400); 
  TH1F *h6 = new TH1F("h6","ssxptar", 200, -0.2, 0.2);

  while(r6.Next()){
       int j;
        cout << "~While loop ssxptar " << j << '\n';

	//if(*ssxptar > -0.04 && *ssxptar < 0.04){
        h6->Fill(*ssxptar, *weight6); 
	j++;
	//	}

  }

  h6->Draw();

  TString integral6;
  integral6.Form("%f",h6->Integral());
  h6->GetXaxis()->SetTitle("Integrated Value:" + integral6);
  cout << integral6 << " ";

  c6->Print(outputpdf);
  //c6->Print("OUTPUT/" + rootfile + "_ssxptar" + ".png");

////////////////////////////////////////////////////////

  TTreeReader r7("h666", f);

  TTreeReaderValue<Float_t> weight7(r7, "Weight");
  TTreeReaderValue<Float_t> missmass(r7, "Em");

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
  integral7.Form("%f",h7->Integral());
  h7->GetXaxis()->SetTitle("Integrated Value:" + integral7);
  cout << integral7 << " ";

  c7->Print(outputpdf + ")");
  //c7->Print("OUTPUT/" + rootfile + "_missmass" + ".png");
  
  ////////////////////////////////////////////////////////

  TTreeReader r8("h666", f);

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
