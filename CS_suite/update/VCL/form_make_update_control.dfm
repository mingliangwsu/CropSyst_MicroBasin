object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'CropSyst Suite update control file generator'
  ClientHeight = 146
  ClientWidth = 357
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  DesignSize = (
    357
    146)
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 0
    Top = 34
    Width = 357
    Height = 13
    Align = alTop
    Caption = 
      'Application installation directory (I.e. for Program files use {' +
      'PF})'
    ExplicitWidth = 308
  end
  object Label2: TLabel
    Left = 0
    Top = 68
    Width = 357
    Height = 13
    Align = alTop
    Caption = 'Application installation URL'
    ExplicitWidth = 128
  end
  object Label3: TLabel
    Left = 0
    Top = 0
    Width = 357
    Height = 13
    Align = alTop
    Caption = 'Distribution_directory'
    ExplicitWidth = 103
  end
  object edit_distribution_directory: TAdvDirectoryEdit
    Left = 0
    Top = 13
    Width = 357
    Height = 21
    Flat = False
    LabelFont.Charset = DEFAULT_CHARSET
    LabelFont.Color = clWindowText
    LabelFont.Height = -11
    LabelFont.Name = 'Tahoma'
    LabelFont.Style = []
    Lookup.Separator = ';'
    Align = alTop
    Color = clWindow
    Enabled = True
    ReadOnly = False
    TabOrder = 0
    Text = 'C:\Installation\CS_suite_4\distribution\cs_suite_4'
    Visible = True
    Version = '1.3.2.4'
    ButtonStyle = bsButton
    ButtonWidth = 18
    Etched = False
    Glyph.Data = {
      CE000000424DCE0000000000000076000000280000000C0000000B0000000100
      0400000000005800000000000000000000001000000000000000000000000000
      8000008000000080800080000000800080008080000080808000C0C0C0000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00F00000000FFF
      00000088888880FF00000B088888880F00000BB08888888000000BBB00000000
      00000BBBBBBB0B0F00000BBB00000B0F0000F000BBBBBB0F0000FF0BBBBBBB0F
      0000FF0BBB00000F0000FFF000FFFFFF0000}
    BrowseDialogText = 'Select Directory'
    ExplicitTop = 8
  end
  object BitBtn1: TBitBtn
    Left = 5
    Top = 113
    Width = 75
    Height = 25
    Anchors = [akLeft, akBottom]
    TabOrder = 1
    OnClick = BitBtn1Click
    Kind = bkOK
    ExplicitTop = 261
  end
  object edit_application_installation_URL: TEdit
    Left = 0
    Top = 81
    Width = 357
    Height = 21
    Align = alTop
    TabOrder = 2
    Text = 'http://www.bsyse.wsu.edu/rnelson/CS_Suite_4'
    ExplicitLeft = 24
    ExplicitTop = 56
    ExplicitWidth = 121
  end
  object edit_installation_directory: TEdit
    Left = 0
    Top = 47
    Width = 357
    Height = 21
    Align = alTop
    TabOrder = 3
    Text = '{PF}\CS_Suite_4'
    ExplicitTop = 53
  end
end
