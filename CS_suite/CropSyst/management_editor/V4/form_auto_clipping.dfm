object auto_clipping_form: Tauto_clipping_form
  Left = 8
  Top = 608
  Width = 578
  Height = 378
  Align = alClient
  Caption = 'auto_clipping_form'
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
  object groupbox_condition: TGroupBox
    Left = 0
    Top = 0
    Width = 570
    Height = 145
    Align = alTop
    Caption = 'Conditions that force clipping/harvest'
    TabOrder = 0
    object Label1: TLabel
      Left = 2
      Top = 15
      Width = 566
      Height = 34
      Align = alTop
      AutoSize = False
      Caption = 
        'Any of the following enabled conditions may trigger the clipping' +
        '/grazing/harvest event. These conditions are '#39'or'#39' not '#39'and'#39', I.e' +
        '. consider growth rate or consder LAI or consider biomass or con' +
        'sider flowering.'
      Color = clInfoBk
      ParentColor = False
      WordWrap = True
    end
    object adjust_rate_clip_checkbox: TAutoCheckBox
      Left = 8
      Top = 53
      Width = 553
      Height = 17
      Hint = 'This growth rate adjustment accelerates or delays clipping '
      Anchors = [akLeft, akTop, akRight]
      Caption = 'Relative growth rate adjustment'
      TabOrder = 0
      OnClick = show_hide_controls
    end
    object adjust_rate_clip_edit: TAutoFloat32EditBar
      Left = 24
      Top = 50
      Width = 534
      Height = 22
      Hint = 
        'This growth rate adjustment accelerates (above 1) or delays clip' +
        'ping (below 1) and it is used as a multiplier to what is conside' +
        'red a low green area index growth rate, which is a fixed value e' +
        'mbedded in the code (0.05 GAI/day). '
      Anchors = [akLeft, akTop, akRight]
      AutoScroll = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 1
      Description_label = 'Relative growth rate adjustment'
      Units_label = '0-2'
    end
    object LAI_forces_clip_checkbox: TAutoCheckBox
      Left = 8
      Top = 75
      Width = 553
      Height = 17
      Hint = 'Clip when LAI is reached'
      Anchors = [akLeft, akTop, akRight]
      Caption = 'Leaf Area Index (LAI) status'
      TabOrder = 2
      OnClick = show_hide_controls
    end
    object LAI_forces_clip_edit: TAutoFloat32EditBar
      Left = 24
      Top = 72
      Width = 534
      Height = 22
      Anchors = [akLeft, akTop, akRight]
      AutoScroll = False
      TabOrder = 3
      Description_label = 'Maximum LAI that forces clipping'
      Units_label = 'm²/m²'
    end
    object biomass_forces_clip_checkbox: TAutoCheckBox
      Left = 8
      Top = 97
      Width = 553
      Height = 17
      Hint = 'Clip when biomass is reached'
      Anchors = [akLeft, akTop, akRight]
      Caption = 'Biomass status'
      TabOrder = 4
      OnClick = show_hide_controls
    end
    object biomass_forces_clip_edit: TAutoFloat32EditBar
      Left = 24
      Top = 94
      Width = 534
      Height = 22
      Anchors = [akLeft, akTop, akRight]
      AutoScroll = False
      TabOrder = 5
      Description_label = 'Maximum biomass that forces clipping'
      Units_label = 'kg/ha'
    end
    object flowering_forces_clip_checkbox: TAutoCheckBox
      Left = 8
      Top = 119
      Width = 552
      Height = 17
      Hint = 'Clip based on flowering'
      Anchors = [akLeft, akTop, akRight]
      Caption = 'Flowering status'
      TabOrder = 6
      OnClick = show_hide_controls
    end
    object flowering_forces_clip_edit: TAutoInt16EditBar
      Left = 24
      Top = 116
      Width = 534
      Height = 22
      Hint = 
        'This is usually used with alfalfa to clip as the plants flower o' +
        'r reflower'
      Anchors = [akLeft, akTop, akRight]
      AutoScroll = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 7
      Description_label = 'Number of days after flowering forces clipping'
      Units_label = 'Days'
    end
  end
  object groupbox_constraints: TGroupBox
    Left = 0
    Top = 145
    Width = 570
    Height = 199
    Align = alClient
    Caption = 'Operation constraints and biomatter fate'
    TabOrder = 1
  end
end
