int t_and_phi_Separated_64a_kaons() {

	TChain *t1 = new TChain("h666");
	t1->Add("fk12_64a.root");

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

  TCut cCuts = "ssdelta>-20 && ssdelta<0 && hsdelta>-9 && hsdelta<4 && missmass<1.15 && hsxptar>-0.065 && hsxptar<0.05 && hsyptar>-0.02 && hsyptar<0.025 && ssxptar>-0.04 && ssxptar<0.04 && ssyptar>-0.03 && ssyptar<0.025";
  TCut cCut1 = Form("Q2>(%f*W+%f)",a,b);
  TCut cCut2 = Form("Q2<(%f*W+%f)",c,d);
  TCut cCut3 = Form("Q2<(%f*W+%f)",e,f);
  TCut cCut4 = Form("Q2>(%f*W+%f)",g,h);

	TCanvas *c1 = new TCanvas("c1","c1",600,600);
	c1->SetTicks(1,1);
	// void, just to get axis
	//Double_t x[] = {0.01,0.65};
        Double_t x[] = {0,1.5};
	Double_t y[2] = {0,0};
	y[1] = 2.0*TMath::Pi()-1.e-8;
	TGraphPolar *gr1 = new TGraphPolar(2,y,x);
	gr1->SetMarkerStyle(7);
	gr1->SetMarkerSize(0);
	gr1->SetTitle("");
	gr1->SetMaxPolar(2.0*TMath::Pi());
	gr1->SetMaxRadial(1.0);
	gr1->Draw("ape");
	c1->Update();
	gr1->GetPolargram()->SetToRadian();
	TH2F *h1a = new TH2F("h1a",";t;phi",36,0,360,10,0,1);
	h1a->SetLineColor(2);
	t1->Draw("t:(phipq*180.0/TMath::Pi())",cCuts && cCut1 && cCut3  ,"goff");
	//t1->Draw("t:phipq",cCuts && cCut1 && cCut2 && cCut3 && cCut4,"goff");
	TGraphPolar *gr1a = new TGraphPolar(t1->GetSelectedRows(),t1->GetV2(),t1->GetV1());
	gr1a->SetTitle("");
	gr1a->SetMarkerStyle(7);
	gr1a->SetMarkerColor(4);
	//gr1a->GetYaxis()->SetNdivisions(500);
	gr1a->Draw("psame");
	gPad->RedrawAxis();
	c1->Print("sim_E1209011_tPOL_64a_kaons.png");
	
	return 0;
}
