#include "TFractionFitter.h"
#include <vector>
#include "BeforeScaling.hpp"
#include "FitAfterScaling.hpp"
#include "SameEventToBackgroundRatio.hpp"
#include "Peaks.hpp"
#include "OnlyPeaks.hpp"
#include "Yields.hpp"
#include "YieldsData.hpp"
#include "TPaveText.h"
#include "Chi2Test.hpp"
#include "ScaleWithUncer.hpp"
#include "YieldScaling.hpp"
#include "PeakComp.hpp"
#include "SignificanceMC.hpp"
#include "QAPlots.hpp"
#include "test.hpp"
#include "TText.h"



std::vector<TH1D*> vHistos;
std::vector<TH1D*> vSignal;
std::vector<TH1D*> vBack;
std::vector<TH1D*> vMean;
std::vector<TH1D*> vSigma;
std::vector<TF1*> vFunctions;
std::vector<TGraphErrors*> vGraphs;

Double_t fitLower = 0.6;                                                        // lower boundary for fitting the background
Double_t fitHigher = 1.1;                                                       // upper boundary for fitting the background

const Int_t nBinsPt_EG1 = 8;                                                    // pT binning for EG 1
std::vector<Double_t> arrPtBinning_EG1
{12.0, 14.0, 16.0, 18.0, 20.0, 24.0, 28.0, 32.0};
// {02.0, 04.0, 06.0, 08.0, 10.0, 12.0, 14.0, 16.0, 18.0, 20.0, 24.0, 28.0, 32.0};

std::vector<Int_t> arrRebinning_EG1
{2, 2, 2, 2, 2, 2, 4};
// {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4};


const Int_t nBinsPt_EG2 = 7;                                                  // pT binning for EG 1
std::vector<Double_t> arrPtBinning_EG2
{  8.0, 12.0, 16.0, 20.0, 24.0,
  28.0, 32.0};

std::vector<Int_t> arrRebinning_EG2
{2, 2, 2, 2, 4, 4};

const Int_t nBinsPt_MB1 = 13;                                                  // pT binning for MB 1
std::vector<Double_t> arrPtBinning_MB1
{02.0, 04.0, 06.0, 08.0, 10.0, 12.0, 14.0, 16.0, 18.0, 20.0, 24.0, 28.0, 32.0};

std::vector<Int_t> arrRebinning_MB1
{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4};

const Int_t nBinsPt_MB2 = 13;                                                  // pT binning for MB 2
std::vector<Double_t> arrPtBinning_MB2
{02.0, 04.0, 06.0, 08.0, 10.0, 12.0, 14.0, 16.0, 18.0, 20.0, 24.0, 28.0, 32.0};

std::vector<Int_t> arrRebinning_MB2
{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4};

/****************************************************************************/
/*                                                                          */
/*             Preparing 1D histo pointer which will be plotted             */
/*                                                                          */
/****************************************************************************/

// ---------------------------------------------------------------------------
//
// Data 1D Histogramm
//
// ---------------------------------------------------------------------------

TH1D* h1_SameEvent_DataOmegaPS_EG1                  = nullptr;
TH1D* h1_Background_DataOmegaRotPS_EG1              = nullptr;
TH1D* h1_Background_DataOmegaTGPSPS_EG1             = nullptr;
TH1D* h1_Background_DataOmegaTGPSPlusPS_EG1         = nullptr;
TH1D* h1_SameEvent_DataOmegaPS_EG2                  = nullptr;
TH1D* h1_Background_DataOmegaRotPS_EG2              = nullptr;
TH1D* h1_Background_DataOmegaTGPSPS_EG2             = nullptr;
TH1D* h1_Background_DataOmegaTGPSPlusPS_EG2         = nullptr;
TH1D* h1_Dalitz_DataOmegaRotPS_EG1                  = nullptr;
TH1D* h1_Dalitz_DataOmegaTGPSPS_EG1                 = nullptr;
TH1D* h1_Dalitz_DataOmegaTGPSPlusPS_EG1             = nullptr;
TH1D* h1_DalitzBack_DataOmegaRotPS_EG1              = nullptr;
TH1D* h1_DalitzBack_DataOmegaTGPSPS_EG1             = nullptr;
TH1D* h1_DalitzBack_DataOmegaTGPSPlusPS_EG1         = nullptr;
TH1D* h1_Dalitz_DataOmegaRotPS_EG2                  = nullptr;
TH1D* h1_Dalitz_DataOmegaTGPSPS_EG2                 = nullptr;
TH1D* h1_Dalitz_DataOmegaTGPSPlusPS_EG2             = nullptr;
TH1D* h1_DalitzBack_DataOmegaRotPS_EG2              = nullptr;
TH1D* h1_DalitzBack_DataOmegaTGPSPS_EG2             = nullptr;
TH1D* h1_DalitzBack_DataOmegaTGPSPlusPS_EG2         = nullptr;
TH1D* h1_Background_DataPi0RotPS_EG1                = nullptr;
TH1D* h1_Background_DataPi0TGPSPlusPS_EG1           = nullptr;
TH1D* h1_Background_DataPi0RotPS_EG2                = nullptr;
TH1D* h1_Background_DataPi0TGPSPlusPS_EG2           = nullptr;
TH1D* h1_DalitzBack_DataPi0RotPS_EG1                = nullptr;
TH1D* h1_DalitzBack_DataPi0TGPSPlusPS_EG1           = nullptr;
TH1D* h1_DalitzBack_DataPi0RotPS_EG2                = nullptr;
TH1D* h1_DalitzBack_DataPi0TGPSPlusPS_EG2           = nullptr;
TH1D* h1_SameEvent_DataOmegaWOPS_EG1                = nullptr;
TH1D* h1_Background_DataOmegaRotWOPS_EG1            = nullptr;
TH1D* h1_Background_DataOmegaTGPSWOPS_EG1           = nullptr;
TH1D* h1_Background_DataOmegaTGPSPlusWOPS_EG1       = nullptr;
TH1D* h1_SameEvent_DataOmegaWOPS_EG2                = nullptr;
TH1D* h1_Background_DataOmegaRotWOPS_EG2            = nullptr;
TH1D* h1_Background_DataOmegaTGPSWOPS_EG2           = nullptr;
TH1D* h1_Background_DataOmegaTGPSPlusWOPS_EG2       = nullptr;
TH1D* h1_Dalitz_DataOmegaRotWOPS_EG1                = nullptr;
TH1D* h1_Dalitz_DataOmegaTGPSWOPS_EG1               = nullptr;
TH1D* h1_Dalitz_DataOmegaTGPSPlusWOPS_EG1           = nullptr;
TH1D* h1_DalitzBack_DataOmegaRotWOPS_EG1            = nullptr;
TH1D* h1_DalitzBack_DataOmegaTGPSWOPS_EG1           = nullptr;
TH1D* h1_DalitzBack_DataOmegaTGPSPlusWOPS_EG1       = nullptr;
TH1D* h1_Dalitz_DataOmegaRotWOPS_EG2                = nullptr;
TH1D* h1_Dalitz_DataOmegaTGPSWOPS_EG2               = nullptr;
TH1D* h1_Dalitz_DataOmegaTGPSPlusWOPS_EG2           = nullptr;
TH1D* h1_DalitzBack_DataOmegaRotWOPS_EG2            = nullptr;
TH1D* h1_DalitzBack_DataOmegaTGPSWOPS_EG2           = nullptr;
TH1D* h1_DalitzBack_DataOmegaTGPSPlusWOPS_EG2       = nullptr;
TH1D* h1_SameEvent_DataOmegaTGPSPlusAPPS1Sigma_EG1  = nullptr;
TH1D* h1_Background_DataOmegaTGPSPlusAPPS1Sigma_EG1 = nullptr;
TH1D* h1_SameEvent_DataOmegaTGPSPlusAPPS2Sigma_EG1  = nullptr;
TH1D* h1_Background_DataOmegaTGPSPlusAPPS2Sigma_EG1 = nullptr;
TH1D* h1_SameEvent_DataOmegaTGPSPlusAPPS3Sigma_EG1  = nullptr;
TH1D* h1_Background_DataOmegaTGPSPlusAPPS3Sigma_EG1 = nullptr;
TH1D* h1_SameEvent_DataOmegaTGPSPlusAPPS1Sigma_EG2  = nullptr;
TH1D* h1_Background_DataOmegaTGPSPlusAPPS1Sigma_EG2 = nullptr;
TH1D* h1_SameEvent_DataOmegaTGPSPlusAPPS2Sigma_EG2  = nullptr;
TH1D* h1_Background_DataOmegaTGPSPlusAPPS2Sigma_EG2 = nullptr;
TH1D* h1_SameEvent_DataOmegaTGPSPlusAPPS3Sigma_EG2  = nullptr;
TH1D* h1_Background_DataOmegaTGPSPlusAPPS3Sigma_EG2 = nullptr;
TH1D* h1_SameEvent_DataOmegaPSNCell_EG1             = nullptr;
TH1D* h1_Background_DataOmegaRotPSNCell_EG1         = nullptr;
TH1D* h1_Background_DataOmegaTGPSPSNCell_EG1        = nullptr;
TH1D* h1_Background_DataOmegaTGPSPlusPSNCell_EG1    = nullptr;
TH1D* h1_SameEvent_DataOmegaPSNCell_EG2             = nullptr;
TH1D* h1_Background_DataOmegaRotPSNCell_EG2         = nullptr;
TH1D* h1_Background_DataOmegaTGPSPSNCell_EG2        = nullptr;
TH1D* h1_Background_DataOmegaTGPSPlusPSNCell_EG2    = nullptr;
TH1D* h1_Dalitz_DataOmegaRotPSNCell_EG1             = nullptr;
TH1D* h1_Dalitz_DataOmegaTGPSPSNCell_EG1            = nullptr;
TH1D* h1_Dalitz_DataOmegaTGPSPlusPSNCell_EG1        = nullptr;
TH1D* h1_DalitzBack_DataOmegaRotPSNCell_EG1         = nullptr;
TH1D* h1_DalitzBack_DataOmegaTGPSPSNCell_EG1        = nullptr;
TH1D* h1_DalitzBack_DataOmegaTGPSPlusPSNCell_EG1    = nullptr;
TH1D* h1_Dalitz_DataOmegaRotPSNCell_EG2             = nullptr;
TH1D* h1_Dalitz_DataOmegaTGPSPSNCell_EG2            = nullptr;
TH1D* h1_Dalitz_DataOmegaTGPSPlusPSNCell_EG2        = nullptr;
TH1D* h1_DalitzBack_DataOmegaRotPSNCell_EG2         = nullptr;
TH1D* h1_DalitzBack_DataOmegaTGPSPSNCell_EG2        = nullptr;
TH1D* h1_DalitzBack_DataOmegaTGPSPlusPSNCell_EG2    = nullptr;


// ---------------------------------------------------------------------------
//
// Data 1D Histogramm Ratios Background and SameEvent
//
// ---------------------------------------------------------------------------
TH1D* h1_Ratio_BackToSame_DataOmegaRotPS_EG1            = nullptr;
TH1D* h1_Ratio_BackToSame_DataOmegaTGPSPS_EG1           = nullptr;
TH1D* h1_Ratio_BackToSame_DataOmegaTGPSPlusPS_EG1       = nullptr;
TH1D* h1_Ratio_BackToSame_DataOmegaRotPS_EG2            = nullptr;
TH1D* h1_Ratio_BackToSame_DataOmegaTGPSPS_EG2           = nullptr;
TH1D* h1_Ratio_BackToSame_DataOmegaTGPSPlusPS_EG2       = nullptr;
TH1D* h1_Ratio_BackToSame_DataPi0RotPS_EG1              = nullptr;
TH1D* h1_Ratio_BackToSame_DataPi0TGPSPlusPS_EG1         = nullptr;
TH1D* h1_Ratio_BackToSame_DataPi0RotPS_EG2              = nullptr;
TH1D* h1_Ratio_BackToSame_DataPi0TGPSPlusPS_EG2         = nullptr;
TH1D* h1_Ratio_BackToSame_DataOmegaRotWOPS_EG1          = nullptr;
TH1D* h1_Ratio_BackToSame_DataOmegaTGPSWOPS_EG1         = nullptr;
TH1D* h1_Ratio_BackToSame_DataOmegaTGPSPlusWOPS_EG1     = nullptr;
TH1D* h1_Ratio_BackToSame_DataOmegaRotWOPS_EG2          = nullptr;
TH1D* h1_Ratio_BackToSame_DataOmegaTGPSWOPS_EG2         = nullptr;
TH1D* h1_Ratio_BackToSame_DataOmegaTGPSPlusWOPS_EG2     = nullptr;
TH1D* h1_Ratio_BackToSame_DataOmegaRotPSNCell_EG1       = nullptr;
TH1D* h1_Ratio_BackToSame_DataOmegaTGPSPSNCell_EG1      = nullptr;
TH1D* h1_Ratio_BackToSame_DataOmegaTGPSPlusPSNCell_EG1  = nullptr;


// ---------------------------------------------------------------------------
//
// Data 1D Histogramm Peak from Ratio Background and SameEvent
//
// ---------------------------------------------------------------------------
TH1D* h1_Peak_BackToSame_DataOmegaRotPS_EG1           = nullptr;
TH1D* h1_Peak_BackToSame_DataOmegaTGPSPS_EG1          = nullptr;
TH1D* h1_Peak_BackToSame_DataOmegaTGPSPlusPS_EG1      = nullptr;
TH1D* h1_Peak_BackToSame_DataOmegaRotPS_EG2           = nullptr;
TH1D* h1_Peak_BackToSame_DataOmegaTGPSPS_EG2          = nullptr;
TH1D* h1_Peak_BackToSame_DataOmegaTGPSPlusPS_EG2      = nullptr;
TH1D* h1_Peak_BackToSame_DataPi0RotPS_EG1             = nullptr;
TH1D* h1_Peak_BackToSame_DataPi0TGPSPlusPS_EG1        = nullptr;
TH1D* h1_Peak_BackToSame_DataPi0RotPS_EG2             = nullptr;
TH1D* h1_Peak_BackToSame_DataPi0TGPSPlusPS_EG2        = nullptr;
TH1D* h1_Peak_BackToSame_DataOmegaRotWOPS_EG1         = nullptr;
TH1D* h1_Peak_BackToSame_DataOmegaTGPSWOPS_EG1        = nullptr;
TH1D* h1_Peak_BackToSame_DataOmegaTGPSPlusWOPS_EG1    = nullptr;
TH1D* h1_Peak_BackToSame_DataOmegaRotWOPS_EG2         = nullptr;
TH1D* h1_Peak_BackToSame_DataOmegaTGPSWOPS_EG2        = nullptr;
TH1D* h1_Peak_BackToSame_DataOmegaTGPSPlusWOPS_EG2    = nullptr;
TH1D* h1_Peak_BackToSame_DataOmegaRotPSNCell_EG1      = nullptr;
TH1D* h1_Peak_BackToSame_DataOmegaTGPSPSNCell_EG1     = nullptr;
TH1D* h1_Peak_BackToSame_DataOmegaTGPSPlusPSNCell_EG1 = nullptr;


// ---------------------------------------------------------------------------
//
// MC 1D Histogramm
//
// ---------------------------------------------------------------------------

TH1D* h1_SameEvent_MCOmegaPS_EG1                  = nullptr;
TH1D* h1_Background_MCOmegaRotPS_EG1              = nullptr;
TH1D* h1_Background_MCOmegaTGPSPS_EG1             = nullptr;
TH1D* h1_Background_MCOmegaTGPSPlusPS_EG1         = nullptr;
TH1D* h1_SameEvent_MCOmegaPS_EG2                  = nullptr;
TH1D* h1_Background_MCOmegaRotPS_EG2              = nullptr;
TH1D* h1_Background_MCOmegaTGPSPS_EG2             = nullptr;
TH1D* h1_Background_MCOmegaTGPSPlusPS_EG2         = nullptr;
TH1D* h1_OmegaInAcc_MC_EG1                        = nullptr;
TH1D* h1_OmegaInAcc_MC_EG2                        = nullptr;
TH1D* h1_OmegaGen_PYTHIA                          = nullptr;
TH1D* h1_OmegaInAcc_PYTHIA                        = nullptr;
TH1D* h1_Dalitz_MCOmegaRotPS_EG1                  = nullptr;
TH1D* h1_Dalitz_MCOmegaTGPSPS_EG1                 = nullptr;
TH1D* h1_Dalitz_MCOmegaTGPSPlusPS_EG1             = nullptr;
TH1D* h1_DalitzBack_MCOmegaRotPS_EG1              = nullptr;
TH1D* h1_DalitzBack_MCOmegaTGPSPS_EG1             = nullptr;
TH1D* h1_DalitzBack_MCOmegaTGPSPlusPS_EG1         = nullptr;
TH1D* h1_TrueDalitz_MCOmegaRotPS_EG1              = nullptr;
TH1D* h1_TrueDalitz_MCOmegaTGPSPS_EG1             = nullptr;
TH1D* h1_TrueDalitz_MCOmegaTGPSPlusPS_EG1         = nullptr;
TH1D* h1_Dalitz_MCOmegaRotPS_EG2                  = nullptr;
TH1D* h1_Dalitz_MCOmegaTGPSPS_EG2                 = nullptr;
TH1D* h1_Dalitz_MCOmegaTGPSPlusPS_EG2             = nullptr;
TH1D* h1_DalitzBack_MCOmegaRotPS_EG2              = nullptr;
TH1D* h1_DalitzBack_MCOmegaTGPSPS_EG2             = nullptr;
TH1D* h1_DalitzBack_MCOmegaTGPSPlusPS_EG2         = nullptr;
TH1D* h1_TrueDalitz_MCOmegaRotPS_EG2              = nullptr;
TH1D* h1_TrueDalitz_MCOmegaTGPSPS_EG2             = nullptr;
TH1D* h1_TrueDalitz_MCOmegaTGPSPlusPS_EG2         = nullptr;
TH1D* h1_Background_MCPi0RotPS_EG1                = nullptr;
TH1D* h1_Background_MCPi0TGPSPlusPS_EG1           = nullptr;
TH1D* h1_TrueOmega_MCPS_EG1                       = nullptr;
TH1D* h1_TrueOmega_MCPS_MB1                       = nullptr;
TH1D* h1_TrueOmega_MCPSNCell_EG1                  = nullptr;
TH1D* h1_TruePi0_MCPS_EG1                         = nullptr;
TH1D* h1_Background_MCPi0RotPS_EG2                = nullptr;
TH1D* h1_Background_MCPi0TGPSPlusPS_EG2           = nullptr;
TH1D* h1_TrueOmega_MCPS_EG2                       = nullptr;
TH1D* h1_TruePi0_MCPS_EG2                         = nullptr;
TH1D* h1_DalitzBack_MCPi0RotPS_EG1                = nullptr;
TH1D* h1_DalitzBack_MCPi0TGPSPlusPS_EG1           = nullptr;
TH1D* h1_TrueDalitz_MCPi0RotPS_EG1                = nullptr;
TH1D* h1_TrueDalitz_MCPi0TGPSPlusPS_EG1           = nullptr;
TH1D* h1_DalitzBack_MCPi0RotPS_EG2                = nullptr;
TH1D* h1_DalitzBack_MCPi0TGPSPlusPS_EG2           = nullptr;
TH1D* h1_TrueDalitz_MCPi0RotPS_EG2                = nullptr;
TH1D* h1_TrueDalitz_MCPi0TGPSPlusPS_EG2           = nullptr;
TH1D* h1_SameEvent_MCOmegaWOPS_EG1                = nullptr;
TH1D* h1_Background_MCOmegaRotWOPS_EG1            = nullptr;
TH1D* h1_Background_MCOmegaTGPSWOPS_EG1           = nullptr;
TH1D* h1_Background_MCOmegaTGPSPlusWOPS_EG1       = nullptr;
TH1D* h1_TrueOmega_MCWOPS_EG1                     = nullptr;
TH1D* h1_TruePi0_MCWOPS_EG1                       = nullptr;
TH1D* h1_SameEvent_MCOmegaWOPS_EG2                = nullptr;
TH1D* h1_Background_MCOmegaRotWOPS_EG2            = nullptr;
TH1D* h1_Background_MCOmegaTGPSWOPS_EG2           = nullptr;
TH1D* h1_Background_MCOmegaTGPSPlusWOPS_EG2       = nullptr;
TH1D* h1_TrueOmega_MCWOPS_EG2                     = nullptr;
TH1D* h1_TruePi0_MCWOPS_EG2                       = nullptr;
TH1D* h1_Dalitz_MCOmegaRotWOPS_EG1                = nullptr;
TH1D* h1_Dalitz_MCOmegaTGPSWOPS_EG1               = nullptr;
TH1D* h1_Dalitz_MCOmegaTGPSPlusWOPS_EG1           = nullptr;
TH1D* h1_DalitzBack_MCOmegaRotWOPS_EG1            = nullptr;
TH1D* h1_DalitzBack_MCOmegaTGPSWOPS_EG1           = nullptr;
TH1D* h1_DalitzBack_MCOmegaTGPSPlusWOPS_EG1       = nullptr;
TH1D* h1_TrueDalitz_MCWOPS_EG1                    = nullptr;
TH1D* h1_Dalitz_MCOmegaRotWOPS_EG2                = nullptr;
TH1D* h1_Dalitz_MCOmegaTGPSWOPS_EG2               = nullptr;
TH1D* h1_Dalitz_MCOmegaTGPSPlusWOPS_EG2           = nullptr;
TH1D* h1_DalitzBack_MCOmegaRotWOPS_EG2            = nullptr;
TH1D* h1_DalitzBack_MCOmegaTGPSWOPS_EG2           = nullptr;
TH1D* h1_DalitzBack_MCOmegaTGPSPlusWOPS_EG2       = nullptr;
TH1D* h1_TrueDalitz_MCWOPS_EG2                    = nullptr;
TH1D* h1_SameEvent_MCOmegaTGPSPlusAPPS1Sigma_EG1  = nullptr;
TH1D* h1_Background_MCOmegaTGPSPlusAPPS1Sigma_EG1 = nullptr;
TH1D* h1_TrueOmega_MCOmegaTGPSPlusAPPS1Sigma_EG1  = nullptr;
TH1D* h1_TruePi0_MCOmegaTGPSPlusAPPS1Sigma_EG1    = nullptr;
TH1D* h1_SameEvent_MCOmegaTGPSPlusAPPS2Sigma_EG1  = nullptr;
TH1D* h1_Background_MCOmegaTGPSPlusAPPS2Sigma_EG1 = nullptr;
TH1D* h1_TrueOmega_MCOmegaTGPSPlusAPPS2Sigma_EG1  = nullptr;
TH1D* h1_TruePi0_MCOmegaTGPSPlusAPPS2Sigma_EG1    = nullptr;
TH1D* h1_SameEvent_MCOmegaTGPSPlusAPPS3Sigma_EG1  = nullptr;
TH1D* h1_Background_MCOmegaTGPSPlusAPPS3Sigma_EG1 = nullptr;
TH1D* h1_TrueOmega_MCOmegaTGPSPlusAPPS3Sigma_EG1  = nullptr;
TH1D* h1_TruePi0_MCOmegaTGPSPlusAPPS3Sigma_EG1    = nullptr;
TH1D* h1_SameEvent_MCOmegaTGPSPlusAPPS1Sigma_EG2  = nullptr;
TH1D* h1_Background_MCOmegaTGPSPlusAPPS1Sigma_EG2 = nullptr;
TH1D* h1_TrueOmega_MCOmegaTGPSPlusAPPS1Sigma_EG2  = nullptr;
TH1D* h1_TruePi0_MCOmegaTGPSPlusAPPS1Sigma_EG2    = nullptr;
TH1D* h1_SameEvent_MCOmegaTGPSPlusAPPS2Sigma_EG2  = nullptr;
TH1D* h1_Background_MCOmegaTGPSPlusAPPS2Sigma_EG2 = nullptr;
TH1D* h1_TrueOmega_MCOmegaTGPSPlusAPPS2Sigma_EG2  = nullptr;
TH1D* h1_TruePi0_MCOmegaTGPSPlusAPPS2Sigma_EG2    = nullptr;
TH1D* h1_SameEvent_MCOmegaTGPSPlusAPPS3Sigma_EG2  = nullptr;
TH1D* h1_Background_MCOmegaTGPSPlusAPPS3Sigma_EG2 = nullptr;
TH1D* h1_TrueOmega_MCOmegaTGPSPlusAPPS3Sigma_EG2  = nullptr;
TH1D* h1_TruePi0_MCOmegaTGPSPlusAPPS3Sigma_EG2    = nullptr;
TH1D* h1_SameEvent_MCOmegaPSNCell_EG1             = nullptr;
TH1D* h1_Background_MCOmegaRotPSNCell_EG1         = nullptr;
TH1D* h1_Background_MCOmegaTGPSPSNCell_EG1        = nullptr;
TH1D* h1_Background_MCOmegaTGPSPlusPSNCell_EG1    = nullptr;
TH1D* h1_SameEvent_MCOmegaPSNCell_EG2             = nullptr;
TH1D* h1_Background_MCOmegaRotPSNCell_EG2         = nullptr;
TH1D* h1_Background_MCOmegaTGPSPSNCell_EG2        = nullptr;
TH1D* h1_Background_MCOmegaTGPSPlusPSNCell_EG2    = nullptr;
TH1D* h1_Dalitz_MCOmegaRotPSNCell_EG1             = nullptr;
TH1D* h1_Dalitz_MCOmegaTGPSPSNCell_EG1            = nullptr;
TH1D* h1_Dalitz_MCOmegaTGPSPlusPSNCell_EG1        = nullptr;
TH1D* h1_DalitzBack_MCOmegaRotPSNCell_EG1         = nullptr;
TH1D* h1_DalitzBack_MCOmegaTGPSPSNCell_EG1        = nullptr;
TH1D* h1_DalitzBack_MCOmegaTGPSPlusPSNCell_EG1    = nullptr;
TH1D* h1_TrueDalitz_MCOmegaRotPSNCell_EG1         = nullptr;
TH1D* h1_TrueDalitz_MCOmegaTGPSPSNCell_EG1        = nullptr;
TH1D* h1_TrueDalitz_MCOmegaTGPSPlusPSNCell_EG1    = nullptr;
TH1D* h1_Dalitz_MCOmegaRotPSNCell_EG2             = nullptr;
TH1D* h1_Dalitz_MCOmegaTGPSPSNCell_EG2            = nullptr;
TH1D* h1_Dalitz_MCOmegaTGPSPlusPSNCell_EG2        = nullptr;
TH1D* h1_DalitzBack_MCOmegaRotPSNCell_EG2         = nullptr;
TH1D* h1_DalitzBack_MCOmegaTGPSPSNCell_EG2        = nullptr;
TH1D* h1_DalitzBack_MCOmegaTGPSPlusPSNCell_EG2    = nullptr;
TH1D* h1_TrueDalitz_MCOmegaRotPSNCell_EG2         = nullptr;
TH1D* h1_TrueDalitz_MCOmegaTGPSPSNCell_EG2        = nullptr;
TH1D* h1_TrueDalitz_MCOmegaTGPSPlusPSNCell_EG2    = nullptr;

// MB for Turn On
TH1D* h1_SameEvent_MCOmegaPS_MB1                  = nullptr;
TH1D* h1_Background_MCOmegaRotPS_MB1              = nullptr;
TH1D* h1_Background_MCOmegaTGPSPS_MB1             = nullptr;
TH1D* h1_Background_MCOmegaTGPSPlusPS_MB1         = nullptr;
TH1D* h1_SameEvent_MCOmegaPS_MB2                  = nullptr;
TH1D* h1_Background_MCOmegaRotPS_MB2              = nullptr;
TH1D* h1_Background_MCOmegaTGPSPS_MB2             = nullptr;
TH1D* h1_Background_MCOmegaTGPSPlusPS_MB2         = nullptr;
TH1D* h1_OmegaInAcc_MC_MB1                        = nullptr;
TH1D* h1_OmegaInAcc_MC_MB2                        = nullptr;
TH1D* h1_Dalitz_MCOmegaRotPS_MB1                  = nullptr;
TH1D* h1_Dalitz_MCOmegaTGPSPS_MB1                 = nullptr;
TH1D* h1_Dalitz_MCOmegaTGPSPlusPS_MB1             = nullptr;
TH1D* h1_DalitzBack_MCOmegaRotPS_MB1              = nullptr;
TH1D* h1_DalitzBack_MCOmegaTGPSPS_MB1             = nullptr;
TH1D* h1_DalitzBack_MCOmegaTGPSPlusPS_MB1         = nullptr;
TH1D* h1_TrueDalitz_MCOmegaRotPS_MB1              = nullptr;
TH1D* h1_TrueDalitz_MCOmegaTGPSPS_MB1             = nullptr;
TH1D* h1_TrueDalitz_MCOmegaTGPSPlusPS_MB1         = nullptr;
TH1D* h1_Dalitz_MCOmegaRotPS_MB2                  = nullptr;
TH1D* h1_Dalitz_MCOmegaTGPSPS_MB2                 = nullptr;
TH1D* h1_Dalitz_MCOmegaTGPSPlusPS_MB2             = nullptr;
TH1D* h1_DalitzBack_MCOmegaRotPS_MB2              = nullptr;
TH1D* h1_DalitzBack_MCOmegaTGPSPS_MB2             = nullptr;
TH1D* h1_DalitzBack_MCOmegaTGPSPlusPS_MB2         = nullptr;
TH1D* h1_TrueDalitz_MCOmegaRotPS_MB2              = nullptr;
TH1D* h1_TrueDalitz_MCOmegaTGPSPS_MB2             = nullptr;
TH1D* h1_TrueDalitz_MCOmegaTGPSPlusPS_MB2         = nullptr;

// ---------------------------------------------------------------------------
//
// MC 1D Histogramm Ratios Background and SameEvent
//
// ---------------------------------------------------------------------------
TH1D* h1_Ratio_BackToSame_MCOmegaRotPS_EG1            = nullptr;
TH1D* h1_Ratio_BackToSame_MCOmegaTGPSPS_EG1           = nullptr;
TH1D* h1_Ratio_BackToSame_MCOmegaTGPSPlusPS_EG1       = nullptr;
TH1D* h1_Ratio_BackToSame_MCOmegaRotPS_EG2            = nullptr;
TH1D* h1_Ratio_BackToSame_MCOmegaTGPSPS_EG2           = nullptr;
TH1D* h1_Ratio_BackToSame_MCOmegaTGPSPlusPS_EG2       = nullptr;
TH1D* h1_Ratio_BackToSame_MCPi0RotPS_EG1              = nullptr;
TH1D* h1_Ratio_BackToSame_MCPi0TGPSPlusPS_EG1         = nullptr;
TH1D* h1_Ratio_BackToSame_MCPi0RotPS_EG2              = nullptr;
TH1D* h1_Ratio_BackToSame_MCPi0TGPSPlusPS_EG2         = nullptr;
TH1D* h1_Ratio_BackToSame_MCOmegaRotWOPS_EG1          = nullptr;
TH1D* h1_Ratio_BackToSame_MCOmegaTGPSWOPS_EG1         = nullptr;
TH1D* h1_Ratio_BackToSame_MCOmegaTGPSPlusWOPS_EG1     = nullptr;
TH1D* h1_Ratio_BackToSame_MCOmegaRotWOPS_EG2          = nullptr;
TH1D* h1_Ratio_BackToSame_MCOmegaTGPSWOPS_EG2         = nullptr;
TH1D* h1_Ratio_BackToSame_MCOmegaTGPSPlusWOPS_EG2     = nullptr;
TH1D* h1_Ratio_BackToSame_MCOmegaRotPSNCell_EG1       = nullptr;
TH1D* h1_Ratio_BackToSame_MCOmegaTGPSPSNCell_EG1      = nullptr;
TH1D* h1_Ratio_BackToSame_MCOmegaTGPSPlusPSNCell_EG1  = nullptr;
TH1D* h1_Ratio_BackToSame_MCOmegaRotPSNCell_EG2       = nullptr;
TH1D* h1_Ratio_BackToSame_MCOmegaTGPSPSNCell_EG2      = nullptr;
TH1D* h1_Ratio_BackToSame_MCOmegaTGPSPlusPSNCell_EG2  = nullptr;

// MB for Turn On
TH1D* h1_Ratio_BackToSame_MCOmegaRotPS_MB1            = nullptr;
TH1D* h1_Ratio_BackToSame_MCOmegaTGPSPS_MB1           = nullptr;
TH1D* h1_Ratio_BackToSame_MCOmegaTGPSPlusPS_MB1       = nullptr;
TH1D* h1_Ratio_BackToSame_MCOmegaRotPS_MB2            = nullptr;
TH1D* h1_Ratio_BackToSame_MCOmegaTGPSPS_MB2           = nullptr;
TH1D* h1_Ratio_BackToSame_MCOmegaTGPSPlusPS_MB2       = nullptr;

// ---------------------------------------------------------------------------
//
// MC 1D Histogramm Peak from Ratio Background and SameEvent
//
// ---------------------------------------------------------------------------
TH1D* h1_Peak_BackToSame_MCOmegaRotPS_EG1           = nullptr;
TH1D* h1_Peak_BackToSame_MCOmegaTGPSPS_EG1          = nullptr;
TH1D* h1_Peak_BackToSame_MCOmegaTGPSPlusPS_EG1      = nullptr;
TH1D* h1_Peak_BackToSame_MCOmegaRotPS_EG2           = nullptr;
TH1D* h1_Peak_BackToSame_MCOmegaTGPSPS_EG2          = nullptr;
TH1D* h1_Peak_BackToSame_MCOmegaTGPSPlusPS_EG2      = nullptr;
TH1D* h1_Peak_BackToSame_MCPi0RotPS_EG1             = nullptr;
TH1D* h1_Peak_BackToSame_MCPi0TGPSPlusPS_EG1        = nullptr;
TH1D* h1_Peak_BackToSame_MCPi0RotPS_EG2             = nullptr;
TH1D* h1_Peak_BackToSame_MCPi0TGPSPlusPS_EG2        = nullptr;
TH1D* h1_Peak_BackToSame_MCOmegaRotWOPS_EG1         = nullptr;
TH1D* h1_Peak_BackToSame_MCOmegaTGPSWOPS_EG1        = nullptr;
TH1D* h1_Peak_BackToSame_MCOmegaTGPSPlusWOPS_EG1    = nullptr;
TH1D* h1_Peak_BackToSame_MCOmegaRotWOPS_EG2         = nullptr;
TH1D* h1_Peak_BackToSame_MCOmegaTGPSWOPS_EG2        = nullptr;
TH1D* h1_Peak_BackToSame_MCOmegaTGPSPlusWOPS_EG2    = nullptr;
TH1D* h1_Peak_BackToSame_MCOmegaRotPSNCell_EG1      = nullptr;
TH1D* h1_Peak_BackToSame_MCOmegaTGPSPSNCell_EG1     = nullptr;
TH1D* h1_Peak_BackToSame_MCOmegaTGPSPlusPSNCell_EG1 = nullptr;
TH1D* h1_Peak_BackToSame_MCOmegaRotPSNCell_EG2      = nullptr;
TH1D* h1_Peak_BackToSame_MCOmegaTGPSPSNCell_EG2     = nullptr;
TH1D* h1_Peak_BackToSame_MCOmegaTGPSPlusPSNCell_EG2 = nullptr;

// MB for Turn on
TH1D* h1_Peak_BackToSame_MCOmegaRotPS_MB1           = nullptr;
TH1D* h1_Peak_BackToSame_MCOmegaTGPSPS_MB1          = nullptr;
TH1D* h1_Peak_BackToSame_MCOmegaTGPSPlusPS_MB1      = nullptr;
TH1D* h1_Peak_BackToSame_MCOmegaRotPS_MB2           = nullptr;
TH1D* h1_Peak_BackToSame_MCOmegaTGPSPS_MB2          = nullptr;
TH1D* h1_Peak_BackToSame_MCOmegaTGPSPlusPS_MB2      = nullptr;