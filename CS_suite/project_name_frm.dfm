object project_name_form: Tproject_name_form
  Left = 327
  Top = 365
  Width = 474
  Height = 121
  Caption = 'Project name'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 8
    Width = 206
    Height = 13
    Caption = 'Enter the name of the project to be created.'
  end
  object Label2: TLabel
    Left = 8
    Top = 32
    Width = 289
    Height = 13
    Caption = 'This project will be created in the CS_suite\Projects directory.'
  end
  object Label3: TLabel
    Left = 8
    Top = 56
    Width = 369
    Height = 33
    AutoSize = False
    Caption = 
      'You can put your projects in any directory. After creating a pro' +
      'ject, you can move the project directory to another directory us' +
      'ing windows explore.'
    WordWrap = True
  end
  object project_name_edit: TEdit
    Left = 232
    Top = 8
    Width = 226
    Height = 21
    Anchors = [akLeft, akTop, akRight]
    TabOrder = 0
    Text = 'new project'
  end
  object BitBtn1: TBitBtn
    Left = 384
    Top = 32
    Width = 75
    Height = 25
    TabOrder = 1
    Kind = bkOK
  end
  object BitBtn2: TBitBtn
    Left = 384
    Top = 64
    Width = 75
    Height = 25
    TabOrder = 2
    Kind = bkCancel
  end
end
