int analysis_kaons_diamond(){
//Overlaying 2D histograms; goal is to find kaons in kaon experiment using two different input files that correspond to different kinematics (for line 106a kaons and line 64a kaons) with same Q2 and W to find the rate of KAONS
//This is the first set of data we will be taking in 2017 for the kaon experiment; Q2 of 0.4 GeV2 and W of 2.45 GeV 
  
  TString loweps, higheps;

  cout << "Please enter high epsilon root name...\n";
  cin >> higheps;

  cout << "Please enter low epsilon root name...\n";
  cin >> loweps;

  

  TString hrootEps = higheps + ".root";
  TString lrootEps = loweps + ".root";

  TChain *h667=new TChain("h666");
  TChain *h666=new TChain("h666");
  h667-> Add(hrootEps);
  h666-> Add(lrootEps);
  //h667-> Add("fk12_8518a.root");
  //h666-> Add("fk12_8518a.root");
//blue colored line 
  Double_t x0 = 2.19;
  Double_t y0 = 3.4;
  Double_t x1 = 2.34;
  Double_t y1 = 2.7;
//yellow colored line
  Double_t x0a = 2.2;
  Double_t y0a = 3.40;
  Double_t x1a = 2.8;
  Double_t y1a = 2.28;

//pink colored line
  Double_t x0b = 2.41;
  Double_t y0b = 2.96;
  Double_t x1b = 2.46;
  Double_t y1b = 2.72;
//teal colored line
  Double_t x0c = 2.49;
  Double_t y0c = 2.49;
  Double_t x1c = 2.34;
  Double_t y1c = 2.78;

//slopes of lines
  Double_t a = (y1-y0)/(x1-x0);
  Double_t b = y1 - a*x1;
  Double_t c = (y1a-y0a)/(x1a-x0a);
  Double_t d = y0a - c*x0a;
  Double_t e = (y1b-y0b)/(x1b-x0b);
  Double_t f = y1b - e*x1b;
  Double_t g = (y1c-y0c)/(x1c-x0c);
  Double_t h = y1c - g*x1c;


  Double_t highepsnormfac= 0.363249E+08; //normalization factor for line
  Double_t lowepsnormfac= 0.178655E+08; //normalization factor for line
  Int_t N1= h667->GetEntries();
  Int_t N2= h666->GetEntries();
 

//check these cuts, especially the hsdelta and ssdelta..in this case the analysis file is called "analysis_106a_64a_1D_kaons.C"
  TCut cSalina = "";
  TCut cCuts = "ssdelta>-15 && ssdelta<15 && hsdelta>-9 && hsdelta<4 && missmass<1.15 && hsxptar>-0.065 && hsxptar<0.05 && hsyptar>-0.02 && hsyptar<0.025 && ssxptar>-0.04 && ssxptar<0.04 && ssyptar>-0.03 && ssyptar<0.025";
  TCut cCut1 = Form("Q2>(%f*W+%f)",a,b);
  TCut cCut2 = Form("Q2<(%f*W+%f)",c,d);
  TCut cCut3 = Form("Q2<(%f*W+%f)",e,f);
  TCut cCut4 = Form("Q2>(%f*W+%f)",g,h);
  
//Creating and drawing two histograms corresponding to the two different input files -106a and 64a...aka Q2 vs. W plot
 TH2F *h3 = new TH2F("h3","", 200, 2, 3, 200, 0, .8);
 TH2F *h3a = new TH2F("h3a","", 200, 2, 3, 200, 0, .8);
 h3a->SetMarkerColor(2);
 TCanvas *c0 = new TCanvas("c0","c0");
 h667->Draw("Q2:W>>h3", (cCuts && cCut1 && cCut2 && cCut3 && cCut4)*Form("(Weight*%g)",highepsnormfac/N1), "hist"); 
 h666->Draw("Q2:W>>h3a", (cCuts && cCut1 && cCut2 && cCut3 && cCut4)*Form("(Weight*%g)",lowepsnormfac/N2), "hist same");

  
  //uncomment below the two lines to see overlayed histograms..but don't forget to comment the two lines above specifying the cuts. Can't simultaneously do that :( 
 h667->Draw("Q2:W>>h3", cCuts , "hist"); 
 h666->Draw("Q2:W>>h3a", cCuts , "hist same");
 
//below code displays lines to help visualize the diamond cuts..comment out using slash and star if you don't want them. You can also adjust these lines.
/*
  TF1 *f1 = new TF1("f1",Form("%f*x+%f",a,b),0,10);
  f1->SetLineColor(4);
  f1->Draw("lsame");
  TF1 *f2 = new TF1("f2",Form("%f*x+%f",c,d),0,10);
  f2->SetLineColor(5);
  f2->Draw("lsame");
  TF1 *f3 = new TF1("f3",Form("%f*x+%f",e,f),0,10);
  f3->SetLineColor(6);
  f3->Draw("lsame");
  TF1 *f4 = new TF1("f4",Form("%f*x+%f",g,h),0,10);
  f4->SetLineColor(7);
  f4->Draw("lsame");
*/
//*/
//title of axes
h3->GetXaxis()->SetTitle("W (GeV)");
h3->GetYaxis()->SetTitle("Q^{2} (GeV^{2})"); 
h3->SetLineColor(2);
h3a->GetXaxis()->SetTitle("W (GeV)");
h3a->GetYaxis()->SetTitle("Q^{2} (GeV^{2})");
h3->Scale(highepsnormfac/N1);
h3a->Scale(lowepsnormfac/N2);
/*
//legend
leg = new TLegend(0.1,0.9,0.38,0.8);
//leg->SetBorderSize(0);
leg->AddEntry(h3, "Q^{2}=3.0 GeV^{2} #epsilon = 0.8800", "l");
leg->AddEntry(h3a, "Q^{2}=3.0 GeV^{2} #epsilon = 0.6070", "l");
leg->Draw();
*/
gStyle->SetOptStat(0); //gets rid of the annoying box

//Now we can find the rate and the number of kaons in this experiment
cout << "Integral (High Epsilon): " << h3->Integral() << endl; //for line 106a
cout << "Integral (Low Epsilon): " << h3a->Integral() << endl; //for line 64a

//Plots the histograms..specify above how you want it to look like (by commenting in or out)  */
c0->Print("2D_DiamondCuts_NoLines_" + higheps + "_AND_" + loweps + ".png");

  return 0;
    }
