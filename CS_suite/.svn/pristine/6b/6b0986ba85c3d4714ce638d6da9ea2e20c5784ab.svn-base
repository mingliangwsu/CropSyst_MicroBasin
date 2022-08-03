object inorganic_N_application_form: Tinorganic_N_application_form
  Left = 2093
  Top = 389
  Align = alClient
  Anchors = [akLeft, akTop, akBottom]
  Caption = 'Inorganic nitrogen application'
  ClientHeight = 299
  ClientWidth = 421
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object nitrate_edit: TRNAutoParameterEditBar
    AlignWithMargins = True
    Left = 3
    Top = 0
    Width = 415
    Height = 22
    Margins.Top = 0
    Align = alTop
    Alignment = taLeftJustify
    BevelOuter = bvNone
    Caption = 'Amount of nitrogen in the form of nitrate (NO3)'
    TabOrder = 0
  end
  object ammonium_edit: TRNAutoParameterEditBar
    AlignWithMargins = True
    Left = 3
    Top = 25
    Width = 415
    Height = 22
    Margins.Top = 0
    Align = alTop
    Alignment = taLeftJustify
    BevelOuter = bvNone
    Caption = 'Amount of nitrogen in the form of ammonium (NH4)'
    TabOrder = 1
  end
  object NH4_volatil_loss_edit: TRNAutoParameterEditBar
    AlignWithMargins = True
    Left = 3
    Top = 50
    Width = 415
    Height = 23
    Margins.Top = 0
    Align = alTop
    Alignment = taLeftJustify
    BevelOuter = bvNone
    TabOrder = 2
    DesignSize = (
      415
      23)
    object NH4_volatil_loss_check: TRNAutoCheckBox
      AlignWithMargins = True
      Left = 0
      Top = 3
      Width = 219
      Height = 17
      Anchors = [akLeft, akTop, akRight]
      Caption = 'NH4 volatilization loss'
      State = cbGrayed
      TabOrder = 4
      OnClick = NH4_volatil_loss_checkClick
    end
  end
  object panel_NRCS_field_op: TPanel
    Left = 0
    Top = 275
    Width = 421
    Height = 24
    Align = alBottom
    Alignment = taLeftJustify
    Caption = 'NRCS field operation'
    TabOrder = 3
    DesignSize = (
      421
      24)
    object button_NRCS_help: TSpeedButton
      Left = 392
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
      ExplicitLeft = 400
    end
    object NRCS_inorganic_field_op_number_combbox: TComboBox
      Left = 112
      Top = 2
      Width = 282
      Height = 21
      Hint = 'Used for surface residue disturbance and fate'
      Anchors = [akLeft, akTop, akRight]
      ParentShowHint = False
      ShowHint = True
      TabOrder = 0
      Text = '(selection is optional but recommended)'
      OnChange = NRCS_inorganic_field_op_number_combboxChange
      Items.Strings = (
        '(optional - unknown - not listed here)'
        'Fert applic. anhyd knife 12 in'
        'Fert applic. deep plcmt hvy shnk'
        'Fert applic. surface broadcast'
        'Fert. applic. anhyd knife 30 in'
        'Fert. applic., strip-till 30 in')
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 76
    Width = 421
    Height = 109
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 4
    object NH4_source_radiogroup: TRNAutoRadioGroup
      Left = 0
      Top = 0
      Width = 185
      Height = 109
      Align = alLeft
      Caption = 'Ammonium source'
      Items.Strings = (
        'Urea'
        'Urea - ammonium nitrate'
        'Ammonium sulfate'
        'Ammonium nitrate'
        'Anhydrous ammonium')
      TabOrder = 0
    end
    object NH4_appl_method_radiogroup: TRNAutoRadioGroup
      Left = 185
      Top = 0
      Width = 236
      Height = 109
      Align = alClient
      Caption = 'Application method'
      Items.Strings = (
        'Surface broadcast'
        'Surface dribble'
        'Incorporated'
        'Injected')
      TabOrder = 1
    end
  end
  object GroupBox1: TGroupBox
    Left = 0
    Top = 185
    Width = 421
    Height = 90
    Align = alBottom
    Caption = 'Conditions for application'
    TabOrder = 5
    object Label1: TLabel
      AlignWithMargins = True
      Left = 14
      Top = 45
      Width = 402
      Height = 13
      Margins.Left = 12
      Align = alTop
      Caption = 'A value of 0 effectively disables the check for critical N.'
      Color = clInfoBk
      ParentColor = False
      Transparent = False
      ExplicitWidth = 262
    end
    object edit_N_soil_critical: TRNAutoParameterEditBar
      AlignWithMargins = True
      Left = 5
      Top = 18
      Width = 411
      Height = 21
      Hint = 'A value of 0 effectively disables the check for critical N.'
      Align = alTop
      Alignment = taLeftJustify
      BevelOuter = bvNone
      Caption = 'Soil critical N'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 0
    end
    object edit_sampling_depth: TRNAutoParameterEditBar
      AlignWithMargins = True
      Left = 5
      Top = 64
      Width = 411
      Height = 21
      Align = alTop
      Alignment = taLeftJustify
      BevelOuter = bvNone
      Caption = 'Sampling depth'
      TabOrder = 1
    end
  end
end
