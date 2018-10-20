void plot_EvtsVs(TString txtFile = ""){
  
  if (txtFile=="") {
  cout << "Please enter beam energy: ";
  cin >> txtFile;
  }
  
  TString filename1 = "heep_" + txtFile + "_Evts";
  TString filename2 = "heep_" + txtFile + "_Yield";
  TString outputpdf;
  TString foutname = "plot_" + filename1;
  outputpdf = "OUTPUT/" + "plot_" + filename1 + ".pdf";
  
  TTree *tr1 = new TTree("tr1", "tr1");
  Int_t ndata1 = tr1->ReadFile(filename1,"evts:theta:momentum:q2");
  tr1->Draw("evts:theta:momentum:q2","","goff");

  TTree *tr2 = new TTree("tr2", "tr2");
  Int_t ndata2 = tr2->ReadFile(filename1,"yield:theta:momentum:simcYield");
  tr2->Draw("yield:theta:momentum:simcYield","","goff");
  
  Double_t *evts, *theta, *momentum, *q2;
  
  evts = tr1->GetV1();
  theta = tr1->GetV2();
  momentum = tr1->GetV3();
  q2 = tr1->GetV4();
  
  Double_t hevts[11], pevts[11];
  
  cout << "start\n";
  
  cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << "events-> ";
  
  for(Int_t i=0;i<11;i++){
  	hevts[i] = evts[i];
  	pevts[i] = evts[11+i];
  	  	
  	cout << hevts[i] << " ";
  	cout << pevts[i] << " ";
  }
  
  cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
  
  TCanvas *c0 = new TCanvas("c0","Number of Event Plots",600, 400);
  c0->SetLogy();
  
  //////////////////////////////////////////////
  
  TGraph *gr1 = new TGraph(ndata1,theta,evts);
  gr1->SetTitle("Events vs Theta;Theta;Number of Events");
  gr1->SetMarkerColor(2);
  gr1->SetMarkerStyle(20);
  gr1->Draw("AP");
  
  TGraph *gr1a = new TGraph(12,theta,hevts);
  gr1a->SetMarkerColor(4);
  gr1a->SetMarkerStyle(20);
  gr1a->Draw("P");
  
  TLegend *leg1 = new TLegend(.75,.75,.89,.89);
  leg1->AddEntry(gr1a, "HMS events", "lep");
  leg1->AddEntry(gr1, "SHMS events", "lep");
  leg1->SetTextSize(0.025);
  leg1->Draw("SAME");

  c0->Print(outputpdf + "(");
  c0->Print("OUTPUT/" + foutname + "_theta.png");
  
  //////////////////////////////////////////////
  
  TGraph *gr2 = new TGraph(ndata1,momentum,evts);
  gr2->SetTitle("Events vs Momentum;Momentum;Number of Events");
  gr2->SetMarkerColor(2);
  gr2->SetMarkerStyle(20);
  gr2->Draw("AP");
  
  TGraph *gr2a = new TGraph(12,momentum,hevts);
  gr2a->SetMarkerColor(4);
  gr2a->SetMarkerStyle(20);
  gr2a->Draw("P");
  
  TLegend *leg2 = new TLegend(.75,.75,.89,.89);
  leg2->AddEntry(gr2a, "HMS events", "lep");
  leg2->AddEntry(gr2, "SHMS events", "lep");
  leg2->SetTextSize(0.025);
  //leg2->Draw("SAME");

  c0->Print(outputpdf);
  c0->Print("OUTPUT/" + foutname + "_momentum.png");
  
  //////////////////////////////////////////////
  
  TGraph *gr3 = new TGraph(ndata1,q2,evts);
  gr3->SetTitle("Events vs Q^2;Q^2;Number of Events");
  gr3->SetMarkerColor(2);
  gr3->SetMarkerStyle(20);
  gr3->Draw("AP");
  
  TGraph *gr3a = new TGraph(12,q2,hevts);
  gr3a->SetMarkerColor(4);
  gr3a->SetMarkerStyle(20);
  gr3a->Draw("P");
  
  TLegend *leg3 = new TLegend(.75,.75,.89,.89);
  leg3->AddEntry(gr3a, "HMS events", "lep");
  leg3->AddEntry(gr3, "SHMS events", "lep");
  leg3->SetTextSize(0.025);
  //leg3->Draw("SAME");

  c0->Print(outputpdf + ")");
  c0->Print("OUTPUT/" + foutname + "_q2.png");
  
 
  


  return;

}
