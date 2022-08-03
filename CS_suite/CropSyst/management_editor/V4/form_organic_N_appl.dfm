object organic_N_application_form: Torganic_N_application_form
  Left = 1697
  Top = 216
  Width = 584
  Height = 392
  Align = alClient
  Caption = 'Organic N application'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 576
    Height = 334
    ActivePage = TabSheet1
    Align = alClient
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = 'Organic manure'
      object manure_type_radiogroup: TAutoRadioGroup
        Left = 0
        Top = 0
        Width = 568
        Height = 73
        Align = alTop
        Caption = 'Organic N (manure) source'
        Columns = 3
        ItemIndex = 7
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
      object NH3_ammonia_edit: TAutoFloat32EditBar
        Left = 0
        Top = 204
        Width = 568
        Height = 22
        Align = alTop
        AutoScroll = False
        TabOrder = 1
        Description_label = 'Amount of nitrogen in the form of ammonia (NH3)'
        Units_label = 'kg/ha'
      end
      object panel_mass: TPanel
        Left = 0
        Top = 73
        Width = 568
        Height = 50
        Align = alTop
        TabOrder = 2
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
          Left = 441
          Top = 28
          Width = 29
          Height = 13
          Anchors = [akTop, akRight]
          Caption = 'kg/ha'
          Visible = False
        end
        object org_N_amount_edit: TAutoFloat32EditBar
          Left = 112
          Top = 3
          Width = 444
          Height = 22
          Anchors = [akLeft, akTop, akRight]
          AutoScroll = False
          TabOrder = 0
          OnExit = org_N_amount_editExit
          Description_label = 'Amount of nitrogen in the form of organic manure'
          Units_label = 'kg/ha'
        end
        object est_org_drymatter_out: TAutoFloat32Edit
          Left = 385
          Top = 25
          Width = 51
          Height = 24
          Alignment = taRightJustify
          Anchors = [akTop, akRight]
          Lines.Strings = (
            '0.00')
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
        object org_N_decomp_time_check: TAutoCheckBox
          Left = 8
          Top = 8
          Width = 540
          Height = 17
          Anchors = [akLeft, akTop, akRight]
          Caption = 'Decomposition time to be calculated by CropSyst'
          TabOrder = 0
          OnClick = org_N_decomp_time_checkClick
        end
        object org_N_decomp_time_50_edit: TAutoInt16EditBar
          Left = 1
          Top = 25
          Width = 579
          Height = 22
          AutoScroll = False
          TabOrder = 1
          Description_label = 'Time required to decompose 50%'
          Units_label = 'Days'
        end
        object org_N_decomp_time_63_edit: TAutoInt16EditBar
          Left = 1
          Top = 49
          Width = 579
          Height = 22
          AutoScroll = False
          TabOrder = 2
          Visible = False
          Description_label = 
            'Time required to decompose 63%  (will be obsolete in version 4.2' +
            ')'
          Units_label = 'Days'
        end
      end
      object edit_carbon_fraction: TAutoFloat32EditBar
        Left = 0
        Top = 226
        Width = 568
        Height = 21
        Align = alTop
        AutoScroll = False
        TabOrder = 4
        Description_label = 'Fraction of carbon in organic matter (carbon fraction)'
        Units_label = '0-1'
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Volatilization'
      ImageIndex = 1
      object including_mineralized_org_n_label: TLabel
        Left = 0
        Top = 22
        Width = 568
        Height = 13
        Align = alTop
        Caption = '        (including mineralized organic N)'
      end
      object NH3_volatil_loss_edit: TAutoFloat32EditBar
        Left = 0
        Top = 0
        Width = 568
        Height = 22
        Align = alTop
        AutoScroll = False
        TabOrder = 0
        Description_label = 'Long term NH3 volatilization'
        Units_label = '%'
      end
      object NH3_volatil_loss_check: TAutoCheckBox
        Left = 8
        Top = 40
        Width = 265
        Height = 17
        Caption = 'Volatilization loss to be calculated by CropSyst'
        TabOrder = 1
        OnClick = NH3_volatil_loss_check_onclick
      end
      object org_appl_method_radiogroup: TAutoRadioGroup
        Left = 280
        Top = 64
        Width = 280
        Height = 241
        Anchors = [akLeft, akTop, akRight, akBottom]
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
        TabOrder = 2
      end
      object orgN_form_radiogroup: TAutoRadioGroup
        Left = 0
        Top = 64
        Width = 281
        Height = 241
        Anchors = [akLeft, akTop, akBottom]
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
        TabOrder = 3
      end
    end
  end
  object panel_NRCS_field_op: TPanel
    Left = 0
    Top = 334
    Width = 576
    Height = 24
    Align = alBottom
    Alignment = taLeftJustify
    Caption = 'NRCS field operation'
    TabOrder = 1
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
      ItemHeight = 13
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
