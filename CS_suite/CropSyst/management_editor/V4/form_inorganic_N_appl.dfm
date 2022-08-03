object inorganic_N_application_form: Tinorganic_N_application_form
  Left = 1002
  Top = 336
  Width = 437
  Height = 250
  Align = alClient
  Anchors = [akLeft, akTop, akBottom]
  Caption = 'Inorganic nitrogen application'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDefaultPosOnly
  PixelsPerInch = 96
  TextHeight = 13
  object nitrate_edit: TAutoFloat32EditBar
    Left = 0
    Top = 0
    Width = 429
    Height = 22
    Align = alTop
    AutoScroll = False
    TabOrder = 0
    Description_label = 'Amount of nitrogen in the form of nitrate (NO3)'
    Units_label = 'kg/ha'
  end
  object ammonium_edit: TAutoFloat32EditBar
    Left = 0
    Top = 22
    Width = 429
    Height = 22
    Align = alTop
    AutoScroll = False
    TabOrder = 1
    Description_label = 'Amount of nitrogen in the form of ammonium (NH4)'
    Units_label = 'kg/ha'
  end
  object NH4_volatil_loss_check: TAutoCheckBox
    Left = 24
    Top = 72
    Width = 249
    Height = 17
    Caption = 'NH4_volatil_loss_check'
    TabOrder = 2
    OnClick = NH4_volatil_loss_checkClick
  end
  object NH4_source_radiogroup: TAutoRadioGroup
    Left = 24
    Top = 88
    Width = 185
    Height = 99
    Anchors = [akLeft, akTop, akBottom]
    Caption = 'Ammonium source'
    ItemIndex = 0
    Items.Strings = (
      'Urea'
      'Urea - ammonium nitrate'
      'Ammonium sulfate'
      'Ammonium nitrate'
      'Anhydrous ammonium'
      'Ammonium nitrosulfate')
    TabOrder = 3
  end
  object NH4_appl_method_radiogroup: TAutoRadioGroup
    Left = 216
    Top = 88
    Width = 185
    Height = 99
    Anchors = [akLeft, akTop, akBottom]
    Caption = 'Application method'
    ItemIndex = 0
    Items.Strings = (
      'Surface broadcast'
      'Surface dribble'
      'Incorporated'
      'Injected')
    TabOrder = 4
  end
  object NH4_volatil_loss_edit: TAutoFloat32EditBar
    Left = 0
    Top = 44
    Width = 429
    Height = 22
    Align = alTop
    AutoScroll = False
    TabOrder = 5
    Description_label = 'NH4 Volatilization loss'
    Units_label = '%'
  end
  object panel_NRCS_field_op: TPanel
    Left = 0
    Top = 192
    Width = 429
    Height = 24
    Align = alBottom
    Alignment = taLeftJustify
    Caption = 'NRCS field operation'
    TabOrder = 6
    object button_NRCS_help: TSpeedButton
      Left = 400
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
    object NRCS_inorganic_field_op_number_combbox: TComboBox
      Left = 112
      Top = 2
      Width = 290
      Height = 21
      Hint = 'Used for surface residue disturbance and fate'
      Anchors = [akLeft, akTop, akRight]
      ItemHeight = 13
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
end
