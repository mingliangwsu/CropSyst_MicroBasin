object form_install_update: Tform_install_update
  Left = 0
  Top = 0
  Caption = 'CS Suite install and/or update'
  ClientHeight = 334
  ClientWidth = 587
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object panel_buttons: TPanel
    Left = 0
    Top = 302
    Width = 587
    Height = 32
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 0
    DesignSize = (
      587
      32)
    object label_status: TLabel
      Left = 256
      Top = 6
      Width = 326
      Height = 26
      Anchors = [akLeft, akTop, akRight]
      AutoSize = False
      Caption = 'Unchecked items will be uninstalled. (not yet implemented)'
      Visible = False
      WordWrap = True
      ExplicitWidth = 186
    end
    object button_update: TBitBtn
      Left = 2
      Top = 6
      Width = 167
      Height = 25
      Caption = 'Begin installation/upgrade'
      Kind = bkOK
      TabOrder = 0
      OnClick = button_updateClick
    end
    object BitBtn2: TBitBtn
      Left = 175
      Top = 6
      Width = 75
      Height = 25
      Kind = bkClose
      TabOrder = 1
      OnClick = BitBtn2Click
    end
  end
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 587
    Height = 302
    ActivePage = tabsheet_setup
    Align = alClient
    TabOrder = 1
    object TabSheet1: TTabSheet
      Caption = 'Download programs and supporting files'
      object label_requires_internet: TLabel
        Left = 0
        Top = 222
        Width = 579
        Height = 26
        Align = alBottom
        Caption = 
          'This program requires an Internet connection.  It contacts our s' +
          'erver at Washington State University to download programs and/or' +
          ' support files to your computer.  '
        Color = clInfoBk
        ParentColor = False
        WordWrap = True
        ExplicitWidth = 550
      end
      object label_additive: TLabel
        Left = 0
        Top = 248
        Width = 579
        Height = 26
        Align = alBottom
        Caption = 
          'Installation is additive: You can install additional components ' +
          'later, or run the install again if your Internet connection fail' +
          's, is unstable or you cancelled the installation.'
        Color = clInfoBk
        ParentColor = False
        WordWrap = True
        ExplicitWidth = 563
      end
      object groupbox_filesets: TGroupBox
        Left = 0
        Top = 111
        Width = 579
        Height = 107
        Align = alTop
        Caption = 
          'File sets (applies only to CropSyst, ClimGen is currently only a' +
          ' complete distribution)'
        TabOrder = 0
        object Label2: TLabel
          Left = 2
          Top = 65
          Width = 575
          Height = 40
          Align = alClient
          Caption = 
            'Documentation includes the context sensitive help.  If documenta' +
            'tion is not installed then context senstive help will be display' +
            'ed from the CropSyst Web server (so documentation is optional if' +
            ' an Internet connection is available.)'
          Color = clInfoBk
          ParentColor = False
          WordWrap = True
          ExplicitWidth = 569
          ExplicitHeight = 26
        end
        object checkbox_programs: TCheckBox
          Left = 2
          Top = 15
          Width = 575
          Height = 17
          Align = alTop
          Caption = 
            'Program files (Includes user interface, simulation model(s) and ' +
            'support files).'
          Checked = True
          State = cbChecked
          TabOrder = 0
        end
        object checkbox_documentation: TCheckBox
          Left = 2
          Top = 32
          Width = 575
          Height = 17
          Align = alTop
          Caption = 'Documentation (Includes manual, help, FAQs, tutorials)'
          Checked = True
          State = cbChecked
          TabOrder = 1
        end
        object checkbox_examples: TCheckBox
          Left = 2
          Top = 49
          Width = 575
          Height = 16
          Align = alTop
          Caption = 'Examples'
          Checked = True
          State = cbChecked
          TabOrder = 2
          Visible = False
        end
      end
      object panel_component_version: TPanel
        Left = 0
        Top = 0
        Width = 579
        Height = 111
        Align = alTop
        TabOrder = 1
        object radio_group_version: TRadioGroup
          Left = 1
          Top = 1
          Width = 49
          Height = 88
          Align = alLeft
          Caption = 'Version'
          ItemIndex = 1
          Items.Strings = (
            '4'
            '5')
          TabOrder = 0
          OnClick = radio_group_versionClick
        end
        object radiogroup_components: TRadioGroup
          Left = 50
          Top = 1
          Width = 528
          Height = 88
          Align = alClient
          Caption = 'Components'
          ItemIndex = 0
          Items.Strings = (
            'CropSyst Suite (Cropping System Simulation - includes ClimGen)'
            'ClimGen (Synthetic weather data generation)'
            
              '(Not yet available) CANMS (Comprehensive Animal Nutrient Managem' +
              'ent System  - includes CropSyst and ClimGen)')
          TabOrder = 1
          OnClick = radiogroup_componentsClick
        end
        object edit_source_URL: TEdit
          Left = 1
          Top = 89
          Width = 577
          Height = 21
          Align = alBottom
          TabOrder = 2
          Text = 
            'http://modeling.bsyse.wsu.edu/rnelson/CS_suite_5/installation/up' +
            'date_control_CropSyst_complete.inf'
          OnChange = edit_source_URLChange
        end
      end
    end
    object tabsheet_setup: TTabSheet
      Caption = 'Setup for Windows'
      ImageIndex = 1
      object Label5: TLabel
        Left = 0
        Top = 0
        Width = 579
        Height = 41
        Align = alTop
        AutoSize = False
        Caption = 
          'These options make minor modifications to the Windows so Windows' +
          ' Explorer can recognize CS suite files and lauch CS applications' +
          '.  (These are optional because some people don'#39't like Windows sy' +
          'stem settings to be modified).'
        Color = clInfoBk
        ParentColor = False
        WordWrap = True
        ExplicitWidth = 476
      end
      object Label4: TLabel
        Left = 0
        Top = 209
        Width = 579
        Height = 65
        Hint = 'For Vista or Win 7'
        Align = alClient
        AutoSize = False
        Caption = 
          'Some of these options may require administrator priviledges to a' +
          'pply to all users. If you receive an error message "Failed to se' +
          't data for" or "Cannot create Key", login as an administrator an' +
          'd click this button again.'
        Color = clInfoBk
        ParentColor = False
        ParentShowHint = False
        ShowHint = True
        WordWrap = True
        ExplicitWidth = 476
        ExplicitHeight = 51
      end
      object GroupBox5: TGroupBox
        Left = 0
        Top = 41
        Width = 579
        Height = 86
        Align = alTop
        Caption = 'Windows Explorer file type associations'
        TabOrder = 0
        object Label3: TLabel
          Left = 2
          Top = 15
          Width = 575
          Height = 28
          Align = alTop
          AutoSize = False
          Caption = 
            'This convenient option tells Windows Explorer (And CS Explorer) ' +
            'how to open CS suite files by clicking on the file in a file lis' +
            't.  (Also gives the files distinctive icons).'
          Color = clInfoBk
          ParentColor = False
          WordWrap = True
          ExplicitWidth = 470
        end
        object button_register_file_types: TBitBtn
          Left = 13
          Top = 49
          Width = 260
          Height = 24
          Caption = 'Associate CS suite file extension/icons in Explorer'
          TabOrder = 0
          OnClick = button_register_file_typesClick
        end
      end
      object GroupBox7: TGroupBox
        Left = 0
        Top = 127
        Width = 579
        Height = 82
        Align = alTop
        Caption = 'Setup shortcuts for all user accounts on this machine'
        TabOrder = 1
        object button_add_icons_all_desktop: TButton
          Left = 2
          Top = 15
          Width = 575
          Height = 25
          Align = alTop
          Caption = 'Add icons to all users'#39' desktops'
          TabOrder = 0
          OnClick = button_add_icons_all_desktopClick
        end
        object button_add_icons_all_start: TButton
          Left = 2
          Top = 40
          Width = 575
          Height = 25
          Align = alTop
          Caption = 'Add icons to all users'#39' Start / Programs / CS suite X '
          TabOrder = 1
          OnClick = button_add_icons_all_startClick
        end
      end
    end
    object tabsheet_installation_status: TTabSheet
      Caption = 'Installation status'
      ImageIndex = 2
      object listbox_installation_status: TListBox
        Left = 0
        Top = 0
        Width = 579
        Height = 274
        Align = alClient
        ItemHeight = 13
        TabOrder = 0
      end
    end
  end
  object WebUpdateWizard_VX: TWebUpdateWizard
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Verdana'
    Font.Style = [fsBold]
    WebUpdate = WebUpdate_VX
    Left = 304
    Top = 24
  end
  object WebUpdate_VX: TWebUpdate
    Agent = 'TWebUpdate'
    DateFormat = 'yyyy-mm-dd'
    DateSeparator = '-'
    LogFileName = 'WUPDATE.LOG'
    PostUpdateInfo.Enabled = False
    Signature = 'WebUpdate'
    TempDirectory = '.'
    TimeFormat = 'hh:nn'
    TimeSeparator = ':'
    URL = 
      'http://modeling.bsyse.wsu.edu/rnelson/CS_suite_5/update_control_' +
      'CropSyst_complete.inf'
    OnProgressCancel = WebUpdate_VXProgressCancel
    OnGetFileList = WebUpdate_VXGetFileList
    Version = '2.2.0.3'
    Left = 336
    Top = 24
  end
  object webcopy_control_files: TWebCopy
    Agent = 'WebCopy'
    DlgCancel = 'Cancel'
    DlgCaption = 'Downloading'
    DlgCompleted = 'completed'
    DlgClose = 'Close'
    DlgFileLabel = 'File :'
    DlgFileOfLabel = 'of'
    DlgFromServerLabel = 'from'
    DlgToServerLabel = 'to'
    DlgProgressLabel = 'Progress :'
    DlgRateLabel = 'Transfer rate :'
    DlgTimeLabel = 'Estimated time left :'
    DlgElapsedTimeLabel = 'Elapsed time :'
    DlgCopying = 'Copying'
    DlgDwnload = 'Downloading'
    DlgUpload = 'Uploading'
    DlgOpenFile = 'Open file'
    DlgOpenFolder = 'Open folder'
    FTPPassive = False
    Items = <
      item
        CopyNewerOnly = True
        FTPPort = 21
        HTTPCommand = hcPost
        Protocol = wpHttp
        TargetDir = 'installation'
        TargetFilename = 'update_control_CropSyst_complete.inf'
        URL = 
          'http://modeling.bsyse.wsu.edu/rnelson/CS_suite_4/installation/up' +
          'date_control_CropSyst_complete.inf'
      end
      item
        FTPPort = 21
        HTTPCommand = hcPost
        Protocol = wpHttp
        TargetDir = 'installation'
        TargetFilename = 'update_control_CropSyst_programs.inf'
        URL = 
          'http://modeling.bsyse.wsu.edu/rnelson/CS_suite_4/installation/up' +
          'date_control_CropSyst_programs.inf'
      end
      item
        FTPPort = 21
        HTTPCommand = hcPost
        Protocol = wpHttp
        TargetDir = 'installation'
        TargetFilename = 'update_control_CropSyst_documentation.inf'
        URL = 
          'http://modeling.bsyse.wsu.edu/rnelson/CS_suite_4/installation/up' +
          'date_control_CropSyst_documentation.inf'
      end
      item
        FTPPort = 21
        HTTPCommand = hcPost
        Protocol = wpHttp
        TargetDir = 'installation'
        TargetFilename = 'update_control_ClimGen_complete.inf'
        URL = 
          'http://modeling.bsyse.wsu.edu/rnelson/CS_suite_4/installation/up' +
          'date_control_ClimGen_complete.inf'
      end>
    ShowCompletion = True
    ShowTime = True
    Timeout = 0
    Version = '2.4.0.1'
    Left = 368
    Top = 24
  end
  object webcopy_files: TWebCopy
    Agent = 'WebCopy'
    DlgCancel = 'Cancel'
    DlgCaption = 'Downloading'
    DlgCompleted = 'completed'
    DlgClose = 'Close'
    DlgFileLabel = 'File :'
    DlgFileOfLabel = 'of'
    DlgFromServerLabel = 'from'
    DlgToServerLabel = 'to'
    DlgProgressLabel = 'Progress :'
    DlgRateLabel = 'Transfer rate :'
    DlgTimeLabel = 'Estimated time left :'
    DlgElapsedTimeLabel = 'Elapsed time :'
    DlgCopying = 'Copying'
    DlgDwnload = 'Downloading'
    DlgUpload = 'Uploading'
    DlgOpenFile = 'Open file'
    DlgOpenFolder = 'Open folder'
    FTPPassive = False
    Items = <>
    ShowCompletion = True
    ShowTime = True
    Timeout = 0
    Version = '2.4.0.1'
    Left = 400
    Top = 24
  end
  object WebUpdate1: TWebUpdate
    Agent = 'TWebUpdate'
    DateFormat = 'dd/mm/yyyy'
    DateSeparator = '/'
    LogFileName = 'WUPDATE.LOG'
    PostUpdateInfo.Enabled = False
    Signature = 'WebUpdate'
    TempDirectory = '.'
    TimeFormat = 'hh:nn'
    TimeSeparator = ':'
    Version = '2.2.0.3'
    Left = 80
    Top = 112
  end
end
