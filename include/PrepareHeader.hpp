#include "plottingheader.hpp"

void PrepareGaussians(std::vector<TF1*> v)
{
  for (int vn = 0; vn < v.size(); vn++)
  {
    v.at(vn)->SetParameters(1.0, 0.782, 0.04);
    v.at(vn)->SetParLimits(0, 0.0, 10000.);
    v.at(vn)->SetParLimits(1, 0.7, 0.85);
    v.at(vn)->SetParLimits(2, 0.01, 0.1);
  }
  return;
}

void PrepareBackground(std::vector<TF1*> v)
{
  for (int vn = 0; vn < v.size(); vn++)
  {
    for(int fn = 0; fn < v.at(vn)->GetNpar(); fn++)
    {
      v.at(vn)->SetParameter(fn, 1.);
    }
  }
  return;
}

void FitBackground(std::vector<TH1D*> vHist, std::vector<TF1*> vFunction, std::vector<TGraphErrors*> vGraph, Double_t low, Double_t high)
{
  for (int vn = 0; vn < vHist.size(); vn++)
  {
    vHist.at(vn)->Fit(vFunction.at(vn), "QM0E", "", low, high);
    vGraph.at(vn)->SetTitle("Fitted pol1 with 1#sigma conf. band");
    for (int i = 1; i <= vHist.at(vn)->GetNbinsX(); i++)
    {
      vGraph.at(vn)->SetPoint(i, vHist.at(vn)->GetBinContent(i), 0);
    }
    // (TVirtualFitter::GetFitter())->GetConfidenceIntervals(vGraph.at(vn), 0.68);
  }
  return;
}

void FitPeak(std::vector<TH1D*> vSignal, std::vector<TH1D*> vBack, std::vector<TH1D*> vMu, std::vector<TH1D*> vSigma, std::vector<TF1*> vFunction, Double_t low, Double_t high, Int_t pTBin)
{
  for (int vn = 0; vn < vSignal.size(); vn++)
  {
    vSignal.at(vn)->Add(vSignal.at(vn), vBack.at(vn), 1, -1);
    vSignal.at(vn)->Fit(vFunction.at(vn), "QM0EB", "", low, high);
    vMu.at(vn)->SetBinContent(pTBin,   vFunction.at(vn)->GetParameter(1));
    vMu.at(vn)->SetBinError(pTBin,     vFunction.at(vn)->GetParError(1));
    vSigma.at(vn)->SetBinContent(pTBin,  vFunction.at(vn)->GetParameter(2));
    vSigma.at(vn)->SetBinError(pTBin,    vFunction.at(vn)->GetParError(2));
  }
  return;
}


void CalcYieldWithEffi(std::vector<TH1D*> vSignal, std::vector<TH1D*> vYield, std::vector<TH1D*> vEffi, std::vector<TF1*> vFunction, Int_t pTBin, Double_t yield_acc, Double_t uncer_acc, Double_t sigma)
{
  Double_t YieldVal = 0.0;
  Double_t YieldUnc = 0.0;
  for (int vn = 0; vn < vSignal.size(); vn++)
  {
    YieldVal = 0.0;
    YieldUnc = 0.0;
    YieldVal = vSignal.at(vn)->IntegralAndError(vSignal.at(vn)->FindBin(vFunction.at(vn)->GetParameter(1) - sigma *vFunction.at(vn)->GetParameter(2)), vSignal.at(vn)->FindBin(vFunction.at(vn)->GetParameter(1) + sigma *vFunction.at(vn)->GetParameter(2)), YieldUnc);

    if(YieldVal > 0.)
    {
      vYield.at(vn)->SetBinContent(pTBin, YieldVal);
      vYield.at(vn)->SetBinError(pTBin, YieldUnc);
    }
    else
    {
      vYield.at(vn)->SetBinContent(pTBin, 0);
      vYield.at(vn)->SetBinError(pTBin, 0);
    }
    vEffi.at(vn)->SetBinContent(pTBin, YieldVal/yield_acc);
    vEffi.at(vn)->SetBinError(pTBin, sqrt(pow(YieldUnc/yield_acc, 2) + pow( ( (YieldVal*uncer_acc)/pow(yield_acc, 2) ), 2) ) );
  }
  return;
}

void CalcYield(std::vector<TH1D*> vSignal, std::vector<TH1D*> vYield, std::vector<TF1*> vFunction, Int_t pTBin, Double_t sigma)
{
  Double_t YieldVal = 0.0;
  Double_t YieldUnc = 0.0;
  for (int vn = 0; vn < vSignal.size(); vn++)
  {
    YieldVal = 0.0;
    YieldUnc = 0.0;
    YieldVal = vSignal.at(vn)->IntegralAndError(vSignal.at(vn)->FindBin(vFunction.at(vn)->GetParameter(1) - sigma * vFunction.at(vn)->GetParameter(2)), vSignal.at(vn)->FindBin(vFunction.at(vn)->GetParameter(1) + sigma * vFunction.at(vn)->GetParameter(2)), YieldUnc);

    if(YieldVal > 0.)
    {
      vYield.at(vn)->SetBinContent(pTBin, YieldVal);
      vYield.at(vn)->SetBinError(pTBin, YieldUnc);
    }
    else
    {
      vYield.at(vn)->SetBinContent(pTBin, 0);
      vYield.at(vn)->SetBinError(pTBin, 0);
    }
  }
  return;
}

void SetZeroOOR(std::vector<TH1D*> vSignal, Double_t low, Double_t high, int &NDF)
{
  NDF = 0;
  for (int vn = 0; vn < vSignal.size(); vn++)
  {
    for (int zerobin = 1; zerobin < vSignal.at(vn)->GetNbinsX(); zerobin++)
    {
      if( (vSignal.at(vn)->GetBinLowEdge(zerobin+1) < low) || (vSignal.at(vn)->GetBinLowEdge(zerobin) >= high))
      {
        vSignal.at(vn)->SetBinContent(zerobin, 0.0);
        vSignal.at(vn)->SetBinError(zerobin, 0.0);
      }
      else
      {
        NDF++;
      }
    }
    vSignal.at(vn)->Scale(1./vSignal.at(vn)->Integral());
  }
  NDF /= vSignal.size();
  return;
}

void CorrAcc(std::vector<TH1D*> vYield, TH1D* hAcc)
{
  for (int vn = 0; vn < vYield.size(); vn++)
  {
    vYield.at(vn)->Divide(vYield.at(vn), hAcc, 1, 1);
  }
  return;
}

void CorrEffi(std::vector<TH1D*> vYield, std::vector<TH1D*> vEffi)
{
  for (int vn = 0; vn < vYield.size(); vn++)
  {
    vYield.at(vn)->Divide(vYield.at(vn), vEffi.at(vn), 1, 1);
  }
  return;
}

Double_t ReversedLogNom(Double_t* x, Double_t* par)
{
  Double_t x1 = x[0];
  return par[3]*exp(-pow(log(par[2]-x1)-par[0], 2.)/(2*pow(par[1], 2.) ) )/( (par[2]-x1)*par[1] );
}

void ScaleMixedEvent(std::vector<TH1D*> vSE, std::vector<TH1D*> vBack, Double_t low, Double_t high)
{
  if(vSE.size() != vBack.size()) {printf("ERROR in ScaleMixedEvent:\n SE and Back vetor unequal lenght!"); exit(4);}
  for (int i = 0; i < vSE.size(); i++)
  {
    vBack.at(i)->Scale(vSE.at(i)->Integral(vSE.at(i)->FindBin(low), vSE.at(i)->FindBin(high) ) / vBack.at(i)->Integral(vBack.at(i)->FindBin(low), vBack.at(i)->FindBin(high) ) );
  }
  return;
}

void CopyInRange(TH1D* h1, TH1D* h2, Double_t low, Double_t high)
{
  for (int iBin = 1, k = 1; iBin <= h1->GetNbinsX(); iBin++)
  {
    if( (h1->GetBinLowEdge(iBin) < low) || (h1->GetBinLowEdge(iBin) >= high) )
    {
      continue;
    }
    else
    {
      h2->SetBinContent(k, h1->GetBinContent(iBin));
      h2->SetBinError(k, h1->GetBinError(iBin));
      k++;
    }
  }
  return;
}
