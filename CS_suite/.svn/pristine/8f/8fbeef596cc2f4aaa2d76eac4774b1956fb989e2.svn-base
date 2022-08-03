object manure_application_form: Tmanure_application_form
  Left = 866
  Top = 590
  Width = 604
  Height = 386
  Align = alClient
  Caption = 'Manure application'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object panel_NRCS_field_op: TPanel
    Left = 0
    Top = 328
    Width = 596
    Height = 24
    Align = alBottom
    Alignment = taLeftJustify
    Caption = 'NRCS field operation'
    TabOrder = 0
    object button_NRCS_help: TSpeedButton
      Left = 567
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
      Width = 457
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
  object ScrollBox1: TScrollBox
    Left = 0
    Top = 0
    Width = 596
    Height = 328
    Align = alClient
    BorderStyle = bsNone
    TabOrder = 1
    object including_mineralized_org_n_label: TLabel
      Left = 0
      Top = 301
      Width = 596
      Height = 26
      Align = alTop
      AutoSize = False
      Caption = 
        'including mineralized organic N (note  changing the Consistency ' +
        'or Appl. method  or amounts will update a default volatilization' +
        ')'
      WordWrap = True
    end
    object fileeditbar_biomatter: TAutoFileEditBar
      Left = 0
      Top = 0
      Width = 596
      Height = 49
      Hint = 
        'Selection of the biomatter/manure description will reset some de' +
        'fault parameters'
      HorzScrollBar.Visible = False
      VertScrollBar.Visible = False
      Align = alTop
      AutoScroll = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 0
      Label = 'Biomatter (Manure or other organic matter) description'
      OnChange = load_manure_description
    end
    object Panel1: TPanel
      Left = 0
      Top = 49
      Width = 596
      Height = 143
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 1
      object groupbox_consistency: TGroupBox
        Left = 0
        Top = 0
        Width = 280
        Height = 143
        Align = alLeft
        Caption = 'Consistency'
        TabOrder = 0
        object edit_dry_matter: TAutoFloat32EditBar
          Left = 2
          Top = 15
          Width = 276
          Height = 21
          Align = alTop
          AutoScroll = False
          TabOrder = 0
          OnExit = edit_dry_matterExit
          Description_label = 'Dry matter'
          Units_label = '%'
        end
        object listbox_form: TListBox
          Left = 2
          Top = 36
          Width = 276
          Height = 105
          Hint = 'Click here to set the corresonding percent dry matter'
          Align = alClient
          Color = cl3DLight
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Courier New'
          Font.Style = []
          ItemHeight = 14
          Items.Strings = (
            'Solid             (> 20% dry matter)'
            'Solid/Semi-solid  (16% dry matter)'
            'Semi solid        (13% dry matter)'
            'Semi solid/Slurry (11% dry matter)'
            'Slurry            (9% dry matter)'
            'Liquid slurry     (6% dry matter)'
            'Liquid            (< 4% dry matter)')
          ParentFont = False
          TabOrder = 1
          OnClick = listbox_formClick
        end
      end
      object org_appl_method_radiogroup: TAutoRadioGroup
        Left = 280
        Top = 0
        Width = 316
        Height = 143
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
        OnClick = org_appl_method_radiogroupClick
      end
    end
    object panel_mass: TPanel
      Left = 0
      Top = 192
      Width = 596
      Height = 65
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 2
      object Label3: TLabel
        Left = 0
        Top = 0
        Width = 105
        Height = 65
        Align = alLeft
        AutoSize = False
        Caption = 
          'Enter either N mass or  biomass (dry basis or wet basis), the ot' +
          'her will be estimated.'
        Color = clInfoBk
        ParentColor = False
        WordWrap = True
      end
      object org_drymatter_label: TLabel
        Left = 136
        Top = 29
        Width = 167
        Height = 13
        Caption = 'Biomatter biomass (dry matter basis) '
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
        Left = 474
        Top = 28
        Width = 29
        Height = 13
        Anchors = [akTop, akRight]
        Caption = 'kg/ha'
        Visible = False
      end
      object Label2: TLabel
        Left = 118
        Top = 44
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
      object Label5: TLabel
        Left = 136
        Top = 45
        Width = 152
        Height = 13
        Caption = 'Biomatter mass (fresh/wet basis)'
        WordWrap = True
      end
      object Label6: TLabel
        Left = 474
        Top = 44
        Width = 29
        Height = 13
        Anchors = [akTop, akRight]
        Caption = 'kg/ha'
        Visible = False
      end
      object label_estimated: TLabel
        Left = 507
        Top = 24
        Width = 86
        Height = 39
        Anchors = [akTop, akRight]
        AutoSize = False
        Caption = 'Estimated from N mass'
        WordWrap = True
      end
      object org_N_amount_edit: TAutoFloat32EditBar
        Left = 112
        Top = 3
        Width = 480
        Height = 22
        Anchors = [akLeft, akTop, akRight]
        AutoScroll = False
        TabOrder = 0
        OnExit = org_N_amount_editExit
        Description_label = 'Nitrogen mass in organic form'
        Units_label = 'kg/ha'
      end
      object edit_est_org_drymatter: TAutoFloat32Edit
        Left = 408
        Top = 25
        Width = 65
        Height = 20
        Alignment = taRightJustify
        Anchors = [akTop, akRight]
        Lines.Strings = (
          '0.00')
        TabOrder = 1
        OnExit = edit_est_org_drymatterExit
      end
      object edit_est_org_wetmatter: TAutoFloat32Edit
        Left = 408
        Top = 42
        Width = 65
        Height = 20
        Alignment = taRightJustify
        Anchors = [akTop, akRight]
        Lines.Strings = (
          '0.00')
        TabOrder = 2
        OnExit = edit_est_org_wetmatterExit
      end
    end
    object NH3_ammonia_edit: TAutoFloat32EditBar
      Left = 0
      Top = 257
      Width = 596
      Height = 22
      Align = alTop
      AutoScroll = False
      TabOrder = 3
      Description_label = 'Amount of nitrogen in the form of ammonia (NH3)'
      Units_label = 'kg/ha'
    end
    object NH3_volatil_loss_edit: TAutoFloat32EditBar
      Left = 0
      Top = 279
      Width = 596
      Height = 22
      Align = alTop
      AutoScroll = False
      TabOrder = 4
      Description_label = 'Long term NH3 volatilization'
      Units_label = '%'
    end
  end
end
