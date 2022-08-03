object form_auto_NO3_application: Tform_auto_NO3_application
  Left = 690
  Top = 421
  Width = 487
  Height = 347
  Caption = 'Automatic NO3 application event'
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
  object Label1: TLabel
    Left = 0
    Top = 22
    Width = 479
    Height = 17
    Align = alTop
    AutoSize = False
    Caption = 
      'The total seasonal application can be split in to 1 or more appl' +
      'ications.'
    Color = clInfoBk
    ParentColor = False
    WordWrap = True
  end
  object Label2: TLabel
    Left = 0
    Top = 39
    Width = 479
    Height = 17
    Align = alTop
    AutoSize = False
    Caption = 'Enter the percent of the total seasonal NO3 to be applied.'
    Color = clInfoBk
    ParentColor = False
    WordWrap = True
  end
  object Label3: TLabel
    Left = 0
    Top = 56
    Width = 479
    Height = 17
    Align = alTop
    AutoSize = False
    Caption = 'Also select the time to make the application. '
    Color = clInfoBk
    ParentColor = False
    WordWrap = True
  end
  object Label4: TLabel
    Left = 0
    Top = 73
    Width = 479
    Height = 17
    Align = alTop
    AutoSize = False
    Caption = 'DO NOT USE EVENT REPETITION, for split application events.'
    Color = clInfoBk
    ParentColor = False
    WordWrap = True
  end
  object percent_of_application_editbar: TAutoInt16EditBar
    Left = 0
    Top = 0
    Width = 479
    Height = 22
    Align = alTop
    AutoScroll = False
    TabOrder = 0
    Description_label = 'Percent of total seasonal application'
    Units_label = '%'
  end
  object panel_auto_N_amount: TPanel
    Left = 0
    Top = 90
    Width = 479
    Height = 223
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 1
  end
end
