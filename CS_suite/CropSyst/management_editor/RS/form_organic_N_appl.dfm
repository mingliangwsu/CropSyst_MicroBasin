object organic_N_application_form: Torganic_N_application_form
  Left = 2107
  Top = 604
  Align = alClient
  Caption = 'Organic N application'
  ClientHeight = 317
  ClientWidth = 576
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  ExplicitWidth = 320
  ExplicitHeight = 240
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 576
    Height = 293
    ActivePage = TabSheet1
    Align = alClient
    TabOrder = 0
    ExplicitHeight = 334
    object TabSheet1: TTabSheet
      Caption = 'Organic manure'
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 306
      object manure_type_radiogroup: TRNAutoRadioGroup
        Left = 0
        Top = 0
        Width = 568
        Height = 73
        Align = alTop
        Caption = 'Organic N (manure) source'
        Columns = 3
        Items.Strings = (
          'Straw (do not use straw here)'
          'Poultry (layers)'
          'Poultry (fresh) broilers or turkeys'
          'Poulty (broilers) or turkeys (aged)'
          'Swine'
          'Dairy (fresh)'
          'Dairy (tank storage)'
          'Dairy (anaerobic lagoon storage)'
          'Beef (fresh)'
          'Beef (aged) 2.5% N (dry wt. basis)'
          'Beef (aged) 1.5% N (dry wt. basis)'
          'Beef (aged) 1.0% N (dry wt. basis)')
        TabOrder = 0
        OnClick = manure_type_radiogroupClick
      end
      object NH3_ammonia_edit: TRNAutoParameterEditBar
        AlignWithMargins = True
        Left = 3
        Top = 207
        Width = 562
        Height = 22
        Align = alTop
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Caption = 'Amount of nitrogen in the form of ammonia (NH3)'
        TabOrder = 1
      end
      object panel_mass: TPanel
        Left = 0
        Top = 73
        Width = 568
        Height = 50
        Align = alTop
        TabOrder = 2
        DesignSize = (
          568
          50)
        object Label3: TLabel
          Left = 1
          Top = 1
          Width = 105
          Height = 48
          Align = alLeft
          AutoSize = False
          Caption = 'Enter either N mass or biomass, the other will be estimated.'
          Color = clInfoBk
          ParentColor = False
          WordWrap = True
        end
        object org_drymatter_label: TLabel
          Left = 136
          Top = 29
          Width = 257
          Height = 20
          AutoSize = False
          Caption = 'Organic dry matter biomass (estimated from N mass)'
          WordWrap = True
        end
        object Label4: TLabel
          Left = 118
          Top = 28
          Width = 12
          Height = 13
          Caption = 'or'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label1: TLabel
          Left = 465
          Top = 31
          Width = 29
          Height = 13
          Anchors = [akTop, akRight]
          Caption = 'kg/ha'
          Visible = False
        end
        object org_N_amount_edit: TRNAutoParameterEditBar
          AlignWithMargins = True
          Left = 112
          Top = 3
          Width = 444
          Height = 22
          Alignment = taLeftJustify
          BevelOuter = bvNone
          Caption = 'Amount of nitrogen in the form of organic manure'
          TabOrder = 0
          OnExit = org_N_amount_editExit
        end
        object est_org_drymatter_out: TRNAutoFloatEdit
          Left = 399
          Top = 26
          Width = 51
          Height = 22
          Alignment = taRightJustify
          Anchors = [akTop, akRight]
          Lines.Strings = (
            '0')
          TabOrder = 1
          OnExit = est_org_drymatter_outChange
        end
      end
      object panel_decomposition: TPanel
        Left = 0
        Top = 123
        Width = 568
        Height = 81
        Align = alTop
        BevelOuter = bvNone
        TabOrder = 3
        object org_N_decomp_time_check: TRNAutoCheckBox
          Left = 0
          Top = 0
          Width = 568
          Height = 17
          Align = alTop
          Caption = 'Decomposition time to be calculated by CropSyst'
          State = cbGrayed
          TabOrder = 0
          OnClick = org_N_decomp_time_checkClick
          ExplicitLeft = 8
          ExplicitTop = 8
          ExplicitWidth = 540
        end
        object org_N_decomp_time_50_edit: TRNAutoParameterEditBar
          AlignWithMargins = True
          Left = 3
          Top = 20
          Width = 562
          Height = 22
          Align = alTop
          Alignment = taLeftJustify
          BevelOuter = bvNone
          Caption = 'Time required to decompose 50%'
          TabOrder = 1
          ExplicitLeft = 1
          ExplicitTop = 25
          ExplicitWidth = 579
        end
        object org_N_decomp_time_63_edit: TRNAutoParameterEditBar
          AlignWithMargins = True
          Left = 3
          Top = 48
          Width = 562
          Height = 22
          Align = alTop
          Alignment = taLeftJustify
          BevelOuter = bvNone
          Caption = 
            'Time required to decompose 63%  (will be obsolete in version 4.2' +
            ')'
          TabOrder = 2
          Visible = False
          ExplicitLeft = 1
          ExplicitTop = 49
          ExplicitWidth = 579
        end
      end
      object edit_carbon_fraction: TRNAutoParameterEditBar
        AlignWithMargins = True
        Left = 3
        Top = 235
        Width = 562
        Height = 21
        Align = alTop
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Caption = 'Fraction of carbon in organic matter (carbon fraction)'
        TabOrder = 4
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Volatilization'
      ImageIndex = 1
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 306
      object including_mineralized_org_n_label: TLabel
        Left = 0
        Top = 28
        Width = 176
        Height = 13
        Align = alTop
        Caption = '        (including mineralized organic N)'
      end
      object NH3_volatil_loss_edit: TRNAutoParameterEditBar
        AlignWithMargins = True
        Left = 3
        Top = 3
        Width = 562
        Height = 22
        Align = alTop
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Caption = 'Long term NH3 volatilization'
        TabOrder = 0
      end
      object NH3_volatil_loss_check: TRNAutoCheckBox
        Left = 0
        Top = 41
        Width = 568
        Height = 17
        Align = alTop
        Caption = 'Volatilization loss to be calculated by CropSyst'
        State = cbGrayed
        TabOrder = 1
        OnClick = NH3_volatil_loss_check_onclick
        ExplicitLeft = 8
        ExplicitTop = 40
        ExplicitWidth = 265
      end
      object panel_volatilization_application: TPanel
        Left = 0
        Top = 58
        Width = 568
        Height = 207
        Align = alClient
        BevelOuter = bvNone
        TabOrder = 2
        ExplicitTop = 104
        ExplicitWidth = 565
        ExplicitHeight = 158
        object orgN_form_radiogroup: TRNAutoRadioGroup
          Left = 0
          Top = 0
          Width = 280
          Height = 207
          Align = alLeft
          Caption = 'Form'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Courier New'
          Font.Style = []
          Items.Strings = (
            'Solid             (> 20% dry matter)'
            'Solid/Semi-solid  (16% dry matter)'
            'Semi solid        (13% dry matter)'
            'Semi solid/Slurry (11% dry matter)'
            'Slurry            (9% dry matter)'
            'Liquid slurry     (6% dry matter)'
            'Liquid            (< 4% dry matter)')
          ParentFont = False
          TabOrder = 0
          ExplicitLeft = 3
          ExplicitTop = 6
          ExplicitHeight = 190
        end
        object org_appl_method_radiogroup: TRNAutoRadioGroup
          Left = 280
          Top = 0
          Width = 288
          Height = 207
          Align = alClient
          Caption = 'Application method'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Courier New'
          Font.Style = []
          Items.Strings = (
            'Surface broadcast no incorporation'
            'Sprinkler'
            'Surface broadcast with incorporation'
            'Knifed')
          ParentFont = False
          TabOrder = 1
          ExplicitHeight = 190
        end
      end
    end
  end
  object panel_NRCS_field_op: TPanel
    Left = 0
    Top = 293
    Width = 576
    Height = 24
    Align = alBottom
    Alignment = taLeftJustify
    Caption = 'NRCS field operation'
    TabOrder = 1
    ExplicitTop = 334
    DesignSize = (
      576
      24)
    object button_NRCS_help: TSpeedButton
      Left = 547
      Top = 1
      Width = 21
      Height = 21
      Anchors = [akTop, akRight]
      Glyph.Data = {
        76010000424D7601000000000000760000002800000020000000100000000100
        04000000000000010000120B0000120B00001000000000000000000000000000
        800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
        3333333333FFFFF3333333333F797F3333333333F737373FF333333BFB999BFB
        33333337737773773F3333BFBF797FBFB33333733337333373F33BFBFBFBFBFB
        FB3337F33333F33337F33FBFBFB9BFBFBF3337333337F333373FFBFBFBF97BFB
        FBF37F333337FF33337FBFBFBFB99FBFBFB37F3333377FF3337FFBFBFBFB99FB
        FBF37F33333377FF337FBFBF77BF799FBFB37F333FF3377F337FFBFB99FB799B
        FBF373F377F3377F33733FBF997F799FBF3337F377FFF77337F33BFBF99999FB
        FB33373F37777733373333BFBF999FBFB3333373FF77733F7333333BFBFBFBFB
        3333333773FFFF77333333333FBFBF3333333333377777333333}
      NumGlyphs = 2
      OnClick = button_NRCS_helpClick
    end
    object NRCS_org_N_field_op_number_combbox: TComboBox
      Left = 112
      Top = 2
      Width = 437
      Height = 21
      Hint = 'Used for surface residue disturbance and fate'
      Anchors = [akLeft, akTop, akRight]
      ParentShowHint = False
      ShowHint = True
      TabOrder = 0
      Text = '(selection is optional but recommended)'
      OnChange = NRCS_org_N_field_op_number_combboxChange
      Items.Strings = (
        '(optional-unknown-not listed)'
        'Graze, continuous'
        'Graze, intensive rotational'
        'Graze, rotational'
        'Graze, stubble or residue'
        'Manure injector'
        'Manure spreader')
    end
  end
end
