object rotation_editor_form: Trotation_editor_form
  Left = 0
  Top = 0
  Caption = 'Rotation'
  ClientHeight = 305
  ClientWidth = 693
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object panel_edit: TPanel
    Left = 0
    Top = 0
    Width = 693
    Height = 57
    Align = alTop
    TabOrder = 0
    object GroupBox1: TGroupBox
      Left = 419
      Top = 1
      Width = 273
      Height = 55
      Align = alRight
      Caption = 'Build rotation'
      TabOrder = 0
      DesignSize = (
        273
        55)
      object label_years: TLabel
        Left = 80
        Top = 32
        Width = 79
        Height = 13
        Anchors = [akTop, akRight]
        Caption = 'Years in rotation'
      end
      object label_end_year: TLabel
        Left = 80
        Top = 13
        Width = 120
        Height = 13
        Anchors = [akTop, akRight]
        Caption = 'Rotation period end year'
      end
      object button_build: TButton
        Left = 3
        Top = 13
        Width = 75
        Height = 39
        Caption = 'Build'
        TabOrder = 0
        OnClick = button_buildClick
      end
      object edit_end: TRNAutoIntegerEdit
        Left = 200
        Top = 10
        Width = 70
        Height = 20
        Alignment = taRightJustify
        Anchors = [akTop, akRight]
        Lines.Strings = (
          '0')
        TabOrder = 1
        WantReturns = False
      end
      object edit_years: TRNAutoIntegerEdit
        Left = 200
        Top = 32
        Width = 70
        Height = 20
        Alignment = taRightJustify
        Anchors = [akTop, akRight]
        Lines.Strings = (
          '0')
        TabOrder = 2
        WantReturns = False
      end
    end
    object button_planting: TBitBtn
      Left = 1
      Top = 1
      Width = 121
      Height = 55
      Align = alLeft
      Caption = 'Add planting event'
      TabOrder = 1
      OnClick = button_plantingClick
    end
    object button_edit: TBitBtn
      Left = 135
      Top = 4
      Width = 75
      Height = 25
      Hint = 
        'In order to replace an entry it must be first highlighted in the' +
        ' list.'
      Caption = 'Edit'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 2
      OnClick = button_editClick
    end
    object button_delete: TBitBtn
      Left = 135
      Top = 30
      Width = 75
      Height = 25
      Caption = 'Delete'
      TabOrder = 3
      OnClick = button_deleteClick
    end
    object button_sort: TBitBtn
      Left = 216
      Top = 4
      Width = 75
      Height = 25
      Caption = 'Sort'
      TabOrder = 4
      OnClick = button_sortClick
    end
  end
  object listbox_rotation: TRNAutoContainerCheckListBox
    Left = 0
    Top = 57
    Width = 693
    Height = 248
    Hint = 'You can use the [x] box to temporarily disable a sowing event.'
    ParentCustomHint = False
    Align = alClient
    ItemHeight = 13
    ParentShowHint = False
    ShowHint = True
    TabOrder = 1
    OnDblClick = listbox_rotationDblClick
  end
end
