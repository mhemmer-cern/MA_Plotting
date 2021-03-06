#include "/home/tavlin/C_Headers/Plotting_Patrick.h"
#include "/home/tavlin/C_Headers/CommonHeader.h"
#include "/home/tavlin/Documents/git/Header/Plot.h"
#include "TLine.h"
#include "TFractionFitter.h"
#include "TGraphErrors.h"
#include "TVirtualFitter.h"
#include <vector>


TLine* line = nullptr;

void SameEventToBackgroundRatio(TH1D* Background, TH1D* Peak, TF1* Background1, TF1* Background2, TPaveText* lSys, TLine* line, TString outname){
  // --- Create TObjArrays -----------------------------------------------------

  std::unique_ptr<TObjArray> main(new TObjArray);
  main->Add(Background);
  main->Add(Peak);
  main->Add(Background1);
  Background1->SetNpx(1000);
  main->Add(Background2);
  Background2->SetNpx(1000);
  main->Add(line);

  // --- Legends ---------------------------------------------------------------
  main->Add(lSys);
  std::unique_ptr<Legend> l(new Legend(main.get(), "ratio\n peak range\n background pol1\n background pol2\n param. range", "lp lp l l l") );


  // --- Marker ----------------------------------------------------------------
  std::vector<Color_t> colors     = {kBlack, kGray+3, kCyan-3, kPink-3, kGray+1, 1, 1};
  std::vector<Style_t> markers    = {kFullCircle, kOpenCircle, 1, 1, 1, 1, 1};
  std::vector<Size_t>  sizes      = {3., 2.5, 3., 3., 5., 1, 1};
  std::vector<Style_t> linestyle  = {1, 1, 1, 1, 1, 1, 1 };
  std::vector<Size_t> linewidth   = {2., 2., 3., 3., 7., 1 ,1 };

  // --- Canvasses -------------------------------------------------------------

  Legend::SetPosition(l.get(), 0.55, 0.9, 0.67, 0.875);

  SquarePlot square = SquarePlot(main.get(), minv_str, "#frac{same event}{background}");
  square.SetMode(Plot::Thesis);
  square.SetStyle(colors, markers, sizes, linestyle, linewidth);
  square.SetRanges(0.0, 1.6, Background->GetMinimum(), Background->GetMaximum());
  square.SetCanvasMargins(0.025, .12, 0.03, .1);

  square.Draw(outname);
  return;

}
