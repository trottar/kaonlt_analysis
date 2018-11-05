int plot_YvC_NOCHER(){
  
  TString filename1 = "eltrack_events_NOCHER.txt";
  TString filename2 = "efficiencies.txt";
  TString filename3 = "beamTime_current.txt";

  TString foutname = "plot_YieldvsCurrent";

  TTree *tr1 = new TTree("tr1", "tr1");
  Int_t ndata1 = tr1->ReadFile(filename1,"runNumber:trEvts");
  tr1->Draw("runNumber:trEvts","","goff");
 
  TTree *tr2 = new TTree("tr2", "tr2");
  Int_t ndata2 = tr2->ReadFile(filename2,"runNumber:eLT:cpuLT:eTrackEff");
  tr2->Draw("runNumber:eLT:cpuLT:eTrackEff","","goff");
  
  TTree *tr3 = new TTree("tr3", "tr3");
  Int_t ndata3 = tr3->ReadFile(filename3,"runNumber:current:bTime");
  tr3->Draw("runNumber:current:bTime","","goff");
  
  Double_t *trEvts = tr1->GetV2();
  Double_t *eLT = tr2->GetV2();
  Double_t *cpuLT = tr2->GetV3();
  Double_t *eTrackEff = tr2->GetV4();
  Double_t *current = tr3->GetV2();
  Double_t *bTime = tr3->GetV3();
  
  Double_t curr, beamTime, charge[9],chargeEff[9], yield[9], yieldRel[9], uncerEvts[9];

  
  
  for(Int_t i=0;i<ndata1;i++){
  charge[i] = current[i]*bTime[i];
  chargeEff[i] = charge[i]*eLT[i]*cpuLT[i]*eTrackEff[i];
  yield[i] = trEvts[i]/chargeEff[i];
  }
 
  for(Int_t i=0;i<ndata1;i++){
    yieldRel[i] = yield[i]/yield[2];
    uncerEvts[i] = TMath::Sqrt(yieldRel[i]);
    cout << runNumber[i] << endl;
    }
  
  TCanvas *c0 = new TCanvas("c0","Carbon, YvC",200,10,700,500);
  c0->SetGrid(5,5);
  //c0->SetTicks(1,1);
  TGraphErrors *gr1 = new TGraphErrors(ndata1,current,yieldRel,0,uncerEvts);
  //gr1->SetLineColor(2);
  //gr1->SetLineWidth(2);
  //gr1->GetYaxis()->SetRangeUser(0,2);
  //gr1->GetYaxis()->SetRangeUser(0,1.2);
  gr1->GetXaxis()->SetRangeUser(0,70);
  gr1->SetTitle("Carbon[1415-1423];Current [uA];Yield");
  gr1->SetMarkerColor(4);
  gr1->SetMarkerStyle(21);
  gr1->Draw("AP");
  c0->Update();
  
  for(Int_t i=0;i<ndata1;i++){
  ofstream myfile;
  	myfile.open ("Yield_Uncer_NOCHER.txt", fstream::app);
  	myfile << "Run Number: " << runNumber[i] << " ";
  	myfile << "Yield Rel: " << yieldRel[i] << " ";
 	myfile << "Uncertainty: +/-" << uncerEvts[i] << endl;
  	myfile.close();
  }

  c0->Print(foutname + "_NOCHER_1415.png");

  return 0;

}
