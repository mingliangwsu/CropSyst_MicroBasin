object operation_event_form: Toperation_event_form
  Left = 424
  Top = 347
  Width = 680
  Height = 499
  HorzScrollBar.Visible = False
  VertScrollBar.Visible = False
  Caption = 'Operation event parameters'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object pagecontrol_operation_event: TPageControl
    Left = 0
    Top = 25
    Width = 672
    Height = 410
    ActivePage = op_param_tabsheet
    Align = alClient
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    object op_param_tabsheet: TTabSheet
      Caption = 'Operation parameters'
    end
    object schedule_tabsheet: TTabSheet
      Caption = 'Schedule'
      ImageIndex = 3
    end
    object tabsheet_duration: TTabSheet
      Caption = 'Duration'
      ImageIndex = 2
      object label_note_duration: TLabel
        Left = 0
        Top = 90
        Width = 664
        Height = 54
        Align = alTop
        AutoSize = False
        Caption = 
          'Currently duration is used in CropSyst only for irrigation and o' +
          'nly full hours are significant (minutes is ignored).  The maximu' +
          'm value for hours is 24 hours per day.  For operations exceeding' +
          ' 24 hours, add additional operations and/or repeat the event.'
        Color = clInfoBk
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentColor = False
        ParentFont = False
        WordWrap = True
      end
      object Label2: TLabel
        Left = 0
        Top = 144
        Width = 664
        Height = 54
        Align = alTop
        AutoSize = False
        Caption = 
          'For CANMS your can specify hours or minutes or both.  The hours ' +
          'and minutes are cumulative to give a total minutes of operation.' +
          '  (typically this should not exceed 1440 minutes per day, but CA' +
          'NMS operations may cross days.'
        Color = clInfoBk
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentColor = False
        ParentFont = False
        Visible = False
        WordWrap = True
      end
      object panel_duration: TPanel
        Left = 0
        Top = 0
        Width = 664
        Height = 65
        Align = alTop
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Caption = 'Duration'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        object label_duration_hours: TLabel
          Left = 192
          Top = 12
          Width = 26
          Height = 13
          Caption = 'hours'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
        end
        object label_duration_minutes: TLabel
          Left = 192
          Top = 36
          Width = 36
          Height = 13
          Caption = 'minutes'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          Visible = False
        end
        object edit_duration_hours: TAutoInt16Edit
          Left = 152
          Top = 8
          Width = 38
          Height = 24
          Hint = 'For CropSyst, this should not exceed 24 hours.'
          Alignment = taRightJustify
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          Lines.Strings = (
            '0')
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
          TabOrder = 0
        end
        object AutoInt16Edit2: TAutoInt16Edit
          Left = 152
          Top = 32
          Width = 38
          Height = 24
          Alignment = taRightJustify
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          Lines.Strings = (
            '0')
          ParentFont = False
          TabOrder = 1
          Visible = False
        end
      end
      object panel_start_hour: TPanel
        Left = 0
        Top = 65
        Width = 664
        Height = 25
        Align = alTop
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Caption = 'Start hour'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 1
        object Label1: TLabel
          Left = 194
          Top = 4
          Width = 151
          Height = 13
          Caption = '24 hour time (Hour 0 is midnight)'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
        end
        object edit_start_hour: TAutoInt16Edit
          Left = 152
          Top = 0
          Width = 38
          Height = 24
          Alignment = taRightJustify
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          Lines.Strings = (
            '0')
          ParentFont = False
          TabOrder = 0
        end
      end
    end
    object tabsheet_LCA: TTabSheet
      Caption = 'Life Cycle Analysis'
      ImageIndex = 3
      object Panel1: TPanel
        Left = 0
        Top = 0
        Width = 664
        Height = 25
        Align = alTop
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Caption = 'Carbon footprint'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        object Label3: TLabel
          Left = 607
          Top = 0
          Width = 57
          Height = 25
          Align = alRight
          Caption = 'kg Ceq / ha'
        end
        object edit_carbon_footprint: TAutoFloat32Edit
          Left = 537
          Top = 0
          Width = 70
          Height = 25
          Align = alRight
          Alignment = taRightJustify
          Lines.Strings = (
            '0.00')
          TabOrder = 0
        end
      end
    end
  end
  object panel_description: TPanel
    Left = 0
    Top = 0
    Width = 672
    Height = 25
    Align = alTop
    Alignment = taLeftJustify
    BevelOuter = bvNone
    Caption = 'Description'
    TabOrder = 1
    object description_edit: TAutoStringEdit
      Left = 64
      Top = 2
      Width = 598
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      TabOrder = 0
      Text = 'description_edit'
    end
  end
  object panel_buttons: TPanel
    Left = 0
    Top = 435
    Width = 672
    Height = 30
    Align = alBottom
    Alignment = taRightJustify
    BevelOuter = bvNone
    Caption = '(Event ID) '
    TabOrder = 2
    object BitBtn1: TBitBtn
      Left = 8
      Top = 2
      Width = 75
      Height = 25
      Caption = 'OK'
      ModalResult = 1
      TabOrder = 0
      Glyph.Data = {
        DE010000424DDE01000000000000760000002800000024000000120000000100
        0400000000006801000000000000000000001000000000000000000000000000
        80000080000000808000800000008000800080800000C0C0C000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
        3333333333333333333333330000333333333333333333333333F33333333333
        00003333344333333333333333388F3333333333000033334224333333333333
        338338F3333333330000333422224333333333333833338F3333333300003342
        222224333333333383333338F3333333000034222A22224333333338F338F333
        8F33333300003222A3A2224333333338F3838F338F33333300003A2A333A2224
        33333338F83338F338F33333000033A33333A222433333338333338F338F3333
        0000333333333A222433333333333338F338F33300003333333333A222433333
        333333338F338F33000033333333333A222433333333333338F338F300003333
        33333333A222433333333333338F338F00003333333333333A22433333333333
        3338F38F000033333333333333A223333333333333338F830000333333333333
        333A333333333333333338330000333333333333333333333333333333333333
        0000}
      NumGlyphs = 2
    end
    object BitBtn2: TBitBtn
      Left = 96
      Top = 2
      Width = 75
      Height = 25
      TabOrder = 1
      Kind = bkCancel
    end
    object help_button: TBitBtn
      Left = 184
      Top = 2
      Width = 75
      Height = 25
      TabOrder = 2
      OnClick = help_button_onclick
      Kind = bkHelp
    end
    object event_ID_edit: TAutoStringEdit
      Left = 272
      Top = 2
      Width = 337
      Height = 21
      Hint = 
        'Enter here any code or brief description that will be displayed ' +
        'in event schedules and output reports.'
      Anchors = [akLeft, akTop, akRight]
      ParentShowHint = False
      ShowHint = True
      TabOrder = 3
      Text = 'event_ID_edit'
    end
  end
end
