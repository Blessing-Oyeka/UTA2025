
// Function to extract 1D histogram: energy vs mode of Y (Reco - True)
TH1D* GetModeProfile(TH2D* h2) {
    if (!h2) return nullptr;

    const TAxis* xaxis = h2->GetXaxis();
    const TAxis* yaxis = h2->GetYaxis();
    int nbinsX = xaxis->GetNbins();

    // Output histogram: same binning in X, Y value = mode from projection
    TH1D* hMode = new TH1D("hMode", "Mode of Reco - True vs Energy;Energy [GeV];Most Probable Reco - True [GeV]",
                           nbinsX, xaxis->GetXmin(), xaxis->GetXmax());

    for (int ix = 1; ix <= nbinsX; ++ix) {
        // Project Y axis at given X bin
        TH1D* hProjY = h2->ProjectionY("_py", ix, ix);
        if (hProjY->GetEntries() == 0) {
            delete hProjY;
            continue;
        }

        int imax = hProjY->GetMaximumBin();
        double modeY = hProjY->GetBinCenter(imax);
        hMode->SetBinContent(ix, modeY);

        delete hProjY;
    }

    return hMode;
}


void GetModeProfileMacro() {
    // Create toy TH2D: energy (X) vs reco - true (Y)
    int nbinsX = 50;
    int nbinsY = 100;
    TH2D* h2 = new TH2D("h2", "Energy vs Reco-True;Energy [GeV];Reco - True [GeV]",
                        nbinsX, 0, 5,   // X: energy from 0 to 5 GeV
                        nbinsY, -1, 1); // Y: reco - true from -1 to 1

    // Fill with toy data (peak at 0.2 shift, broader at higher energies) DONT NEED
    TRandom3 rand(0);
    for (int i = 0; i < 100000; ++i) {
        double E = rand.Uniform(0, 5);
        double shift = 0.2 + 0.05 * E;
        double recoTrue = rand.Gaus(shift, 0.1 + 0.02 * E);
        h2->Fill(E, recoTrue);
    }

    // Get mode profile
    TH1D* hMode = GetModeProfile(h2);
    hMode->SetLineColor(kRed);
    hMode->SetLineWidth(2);
    
    // Draw results
    TCanvas* c1 = new TCanvas();
    h2->Draw("colz");
    c1->SaveAs("TH2DExample.pdf");
    
    TCanvas* c2 = new TCanvas();
    hMode->Draw("hist");
    c2->SaveAs("ModeProfile.pdf");
}

