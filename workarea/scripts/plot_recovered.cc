using namespace std;

void plot_recovered(){
    
    TFile *fin = new TFile("../files/icarus_ana_out.root", "READ");
    TH1D *hTrueEnu_0pi = (TH1D*)fin->Get("hTrueEnu_0pi");
    TH1D *hTrueEnu_Npi = (TH1D*)fin->Get("hTrueEnu_Npi");
    //hTrueEnu_0pi->SetFillColor(kRed);
    //hTrueEnu_Npi->SetFillColor(kBlue);
    hTrueEnu_0pi->SetFillStyle(0);
    hTrueEnu_0pi->SetLineColor(kRed);

    hTrueEnu_Npi->SetFillStyle(0);
    hTrueEnu_Npi->SetLineColor(kBlue);
    

    TCanvas* c1 = new TCanvas();
    THStack* hsEnu = new THStack("","");
    hsEnu->Add(hTrueEnu_0pi);
    hsEnu->Add(hTrueEnu_Npi);
    hsEnu->Draw("hist");
   

    hsEnu->GetXaxis()->SetTitle("True Neutrino Energy");
    hsEnu->GetYaxis()->SetTitle("Entries");

    TLegend *legend = new TLegend(0.65, 0.75, 0.88, 0.88);
    legend->AddEntry(hTrueEnu_0pi, "#nu_{#mu} cc 0#pi", "f");
    legend->AddEntry(hTrueEnu_Npi, "#nu_{#mu} cc N#pi", "f");
    legend->SetBorderSize(0);
    legend->SetFillStyle(0);
    legend->Draw();

    c1->SaveAs("../plots/test2.pdf");
    


    

				      
}
