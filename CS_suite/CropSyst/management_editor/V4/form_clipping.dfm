object clipping_form: Tclipping_form
  Left = 537
  Top = 117
  Width = 563
  Height = 874
  Align = alClient
  Caption = 'Harvest/Clipping'
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
  object scrollbox_removal_mode_and_constraints: TScrollBox
    Left = 0
    Top = 0
    Width = 555
    Height = 840
    Align = alClient
    BorderStyle = bsNone
    TabOrder = 0
    object remove_percentage_note: TLabel
      Left = 0
      Top = 185
      Width = 555
      Height = 41
      Align = alTop
      AutoSize = False
      Caption = 
        'With this mode, the current above ground biomass is divied up ac' +
        'cording to the biomass fate percentages.  The amount removed for' +
        ' beneficial use is considered the yield of the clipping event.'
      Color = clInfoBk
      ParentColor = False
      WordWrap = True
    end
    object panel_NRCS_field_op: TPanel
      Left = 0
      Top = 0
      Width = 555
      Height = 24
      Align = alTop
      Alignment = taLeftJustify
      BevelOuter = bvNone
      Caption = 'NRCS field operation'
      TabOrder = 0
      object SpeedButton1: TSpeedButton
        Left = 528
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
      object NRCS_harvest_field_op_number_combbox: TComboBox
        Left = 112
        Top = 2
        Width = 415
        Height = 21
        Hint = 'Used for surface residue disturbance and fate'
        Anchors = [akLeft, akTop, akRight]
        ItemHeight = 13
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
        Text = '(selection is optional but recommended)'
        OnChange = NRCS_harvest_field_op_number_combboxChange
        Items.Strings = (
          '(unknown - not listed here)'
          'Mower, swather, windrower'
          'Pruning'
          'Harvest, banana'
          'Harvest, banana remove stem'
          'Harvest, broccoli and cauliflower'
          'Harvest, cabbage and head lettuce'
          'Harvest, corn silage with cover crop'
          'Harvest, cotton'
          'Harvest, cotton and shred'
          'Harvest, cut flowers'
          'Harvest, forage sorghum'
          'Harvest, grain, grow cover'
          'Harvest, grass or legume seed, leave forage'
          'Harvest, grass seed, remove forage'
          'Harvest, hand pick'
          'Harvest, hand pull'
          'Harvest, hay, grass'
          'Harvest, hay, legume'
          'Harvest, hay, no regrowth'
          'Harvest, kenaf'
          'Harvest, killing crop'
          'Harvest, leafy veg.'
          'Harvest, legume seed, remove forage'
          'Harvest, peanut digger'
          'Harvest, plantains'
          'Harvest, root crops, digger'
          'Harvest, rootcrops, manually'
          'Harvest, silage'
          'Harvest, snapper header'
          'Harvest, stripper header'
          'Harvest, sugarcane, after burning'
          'Harvest, sugarcane, modern'
          'Harvest, sugarcane, old type'
          'Harvest, tobacco, burley'
          'Harvest, tobacco, flue cured'
          'Graze, continuous'
          'Graze, intensive rotational'
          'Graze, rotational'
          'Graze, stubble or residue')
      end
    end
    object harvest_amount_mode_radiogroup: TAutoRadioGroup
      Left = 0
      Top = 24
      Width = 555
      Height = 57
      Hint = 
        'When you change the biomass removal mode you need to make sure b' +
        'iomass fate sums to 100%'
      Align = alTop
      Caption = 'Mode selection'
      Items.Strings = (
        
          'Single harvest event with primary yield  based harvest index, or' +
          ' harvestable biomatter such as fruits'
        'Remove fixed amount of biomass (suitable for clipping, grazing).'
        'Remove biomass based on percentages')
      ParentShowHint = False
      ShowHint = True
      TabOrder = 1
      OnClick = harvest_amount_mode_radiogroup_onclick
    end
    object panel_clipping_automatic_modes: TPanel
      Left = 8
      Top = 35
      Width = 495
      Height = 17
      Alignment = taLeftJustify
      Anchors = [akLeft, akTop, akRight]
      BevelOuter = bvNone
      Caption = 'Automatic clipping removal modes:'
      TabOrder = 2
    end
    object groupbox_remove_fixed_amount: TGroupBox
      Left = 0
      Top = 81
      Width = 555
      Height = 104
      Align = alTop
      Caption = 'Removed fixed amount of biomass'
      TabOrder = 3
      object remove_fixed_mode_note: TLabel
        Left = 2
        Top = 61
        Width = 551
        Height = 41
        Align = alBottom
        AutoSize = False
        Caption = 
          'With this mode, all the removed amount is divided into the speci' +
          'fied biomatter fate pools'
        Color = clInfoBk
        ParentColor = False
        WordWrap = True
      end
      object remove_fixed_amount_edit: TAutoFloat32EditBar
        Left = 2
        Top = 15
        Width = 551
        Height = 22
        Hint = 'This is the fixed amount of material to remove'
        Align = alTop
        AutoScroll = False
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
        Description_label = 'Fixed amount to remove'
        Units_label = 'kg/ha'
      end
      object accept_less_checkbox: TAutoCheckBox
        Left = 24
        Top = 38
        Width = 527
        Height = 17
        Hint = 
          'If this box is not check, the operation will fail and not be per' +
          'formed if there is insufficient biomass.'
        Anchors = [akLeft, akTop, akRight]
        Caption = 
          'Accept a lesser amount of biomass removed if there is enough bio' +
          'mass to meet the reserve'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 1
      end
    end
    object groupbox_retention: TGroupBox
      Left = 0
      Top = 226
      Width = 555
      Height = 152
      Align = alTop
      Caption = 'Retention (unavailable for clipping/grazing)'
      TabOrder = 4
      object Label9: TLabel
        Left = 2
        Top = 118
        Width = 551
        Height = 32
        Align = alBottom
        AutoSize = False
        Caption = 
          'Any remaining biomass (reserve) is left as standing biomass (dea' +
          'd residue if terminate crop is enabled).'
        Color = clInfoBk
        ParentColor = False
        WordWrap = True
      end
      object notea: TLabel
        Left = 2
        Top = 93
        Width = 551
        Height = 25
        Align = alBottom
        AutoSize = False
        Caption = 
          'This parameter ensures that sufficient green area index is maint' +
          'ained for regrowth when the biomass is removed. Actual biomass r' +
          'emoval may be limited to preserve the GAI.'
        Color = clInfoBk
        ParentColor = False
        WordWrap = True
      end
      object Label16: TLabel
        Left = 2
        Top = 36
        Width = 551
        Height = 37
        Align = alTop
        AutoSize = False
        Caption = 
          'The parameter represent biomass that cannot be physically remove' +
          'd by implements or animals.  Or biomass that is typically left o' +
          'n the field.'
        Color = clInfoBk
        ParentColor = False
        WordWrap = True
      end
      object reserve_biomass_editbar: TAutoFloat32EditBar
        Left = 2
        Top = 15
        Width = 551
        Height = 21
        Hint = 
          'Primarily for grazing operations, this is used to indicate that ' +
          'some biomass cannot or should not be removed.'
        Align = alTop
        AutoScroll = False
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
        Description_label = 'Reserve biomass'
        Units_label = 'kg/ha'
      end
      object min_retain_GAI_edit: TAutoFloat32EditBar
        Left = 2
        Top = 73
        Width = 551
        Height = 21
        Hint = 
          'This value insures that a minimal amount of GAI is retained in t' +
          'he field, this is to prevent the operation from removing so much' +
          ' green foliage that the crop is unable to recover.  (This may li' +
          'mit biomass removal)'
        Align = alTop
        AutoScroll = False
        ParentShowHint = False
        ShowHint = True
        TabOrder = 1
        Description_label = 'Minimum GAI to be retained'
        Units_label = 'units'
      end
    end
    object groupbox_termination: TGroupBox
      Left = 0
      Top = 713
      Width = 555
      Height = 44
      Align = alTop
      Caption = 'Termination'
      TabOrder = 5
      object terminate_crop_label: TLabel
        Left = 120
        Top = 10
        Width = 431
        Height = 29
        Anchors = [akLeft, akTop, akRight]
        AutoSize = False
        Caption = 
          'Terminating the crop kills the crop, and any remaining live biom' +
          'atter will be added to dead standing residue.'
        Color = clInfoBk
        ParentColor = False
        WordWrap = True
      end
      object terminate_crop_checkbox: TAutoCheckBox
        Left = 8
        Top = 16
        Width = 105
        Height = 17
        Caption = 'Terminate crop'
        TabOrder = 0
        OnClick = terminate_crop_checkboxClick
      end
    end
    object groupbox_biomass_disposition: TGroupBox
      Left = 0
      Top = 378
      Width = 555
      Height = 335
      Align = alTop
      Caption = 'Biomass disposition'
      TabOrder = 6
      object harvest_mode_page_control: TPageControl
        Left = 2
        Top = 15
        Width = 551
        Height = 164
        Hint = 
          'Select one of these biomass fate modes. The parameters specific ' +
          'to the mode will be displayed.'
        ActivePage = primary_yield_tabsheet
        Align = alTop
        ParentShowHint = False
        ShowHint = True
        Style = tsButtons
        TabOrder = 0
        OnChange = harvest_mode_onchange
        object primary_yield_tabsheet: TTabSheet
          Caption = 'Grain, tuber, leaf, fruit or root yield'
          object Label2: TLabel
            Left = 0
            Top = 0
            Width = 543
            Height = 33
            Align = alTop
            AutoSize = False
            Caption = 
              'For crop where the yield biomass is grain, fruit, flower or leaf' +
              ' head, roots or tubers; crop parameters specify the primary harv' +
              'ested biomatter based on harvest index or the accumulation of th' +
              'e yield biomass. '
            Color = clInfoBk
            ParentColor = False
            WordWrap = True
          end
          object Label1: TLabel
            Left = 0
            Top = 65
            Width = 543
            Height = 41
            Align = alTop
            AutoSize = False
            Caption = 
              'Remaining biomass (excluding yield) will be disposed as specifie' +
              'd below.  If the crop does not have harvest index or no availabl' +
              'e yield, all above ground biomass is disposed thusly.  For most ' +
              'crops, enable "Terminate crop".'
            Color = clInfoBk
            ParentColor = False
            WordWrap = True
          end
          object Label14: TLabel
            Left = 0
            Top = 33
            Width = 543
            Height = 32
            Align = alTop
            AutoSize = False
            Caption = 
              'This harvest mode is intended for such crops and is usually sche' +
              'duled to harvest when the crop reachs physiological maturity. '
            Color = clInfoBk
            ParentColor = False
            WordWrap = True
          end
          object Label15: TLabel
            Left = 0
            Top = 120
            Width = 543
            Height = 13
            Align = alBottom
            Caption = 'Of the biomass that is not primary yield, the remaining '
          end
          object suggested_harvest_button: TBitBtn
            Left = 368
            Top = 107
            Width = 175
            Height = 25
            Anchors = [akRight, akBottom]
            Caption = 'Enter suggested values'
            TabOrder = 0
            OnClick = suggested_harvest_buttonClick
            Glyph.Data = {
              76010000424D7601000000000000760000002800000020000000100000000100
              04000000000000010000120B0000120B00001000000000000000000000000000
              800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
              FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333393333
              333333333337F3333333333333397333333333333337FF333333333333C94333
              3333333333737F333333333333C9473333333333337373F3333333333CC94433
              3333333337F7F7F3333333333CC94473333333333737F73F33333333CCC94443
              333333337F37F37F33333333CCC94447333333337337F373F333333CCCC94444
              33333337F337F337F333333CCCC94444733333373337F3373F3333CCCCC94444
              4333337F3337FF337F3333CCCCC94444473333733F7773FF73F33CCCCC393444
              443337F37737F773F7F33CCC33393374447337F73337F33737FFCCC333393333
              444377733337F333777FC3333339333337437333333733333373}
            NumGlyphs = 2
          end
        end
        object clipping_tabsheet: TTabSheet
          Caption = 'Clipping'
          ImageIndex = 1
          object Label3: TLabel
            Left = 0
            Top = 0
            Width = 543
            Height = 17
            Align = alTop
            AutoSize = False
            Caption = 
              'This option is used primarily for crops where there may be multi' +
              'ple clipping events during the growing season.'
            Color = clInfoBk
            ParentColor = False
            WordWrap = True
          end
          object Label5: TLabel
            Left = 0
            Top = 67
            Width = 543
            Height = 38
            Align = alTop
            AutoSize = False
            Caption = 
              'Reminder: You can schedule clipping as a repeated event if it is' +
              ' to occur at fixed intervals, or add multiple clipping events to' +
              ' the schedule.  This mode is usually not used to terminate the c' +
              'rop.'
            Color = clInfoBk
            ParentColor = False
            WordWrap = True
          end
          object Label12: TLabel
            Left = 0
            Top = 50
            Width = 543
            Height = 17
            Align = alTop
            AutoSize = False
            Caption = 
              ' In this case all biomass is removed as specified below overridi' +
              'ng any harvest index or other crop harvest parameters.'
            Color = clInfoBk
            ParentColor = False
            WordWrap = True
          end
          object Label13: TLabel
            Left = 0
            Top = 17
            Width = 543
            Height = 33
            Align = alTop
            AutoSize = False
            Caption = 
              'This mode can be used with crops that are normally harvested for' +
              ' primary yield, but are are sometimes harvested prior to physiol' +
              'ogical maturity for fodder, silage or other uses. '
            Color = clInfoBk
            ParentColor = False
            WordWrap = True
          end
          object clipping_fate_label: TLabel
            Left = 0
            Top = 120
            Width = 543
            Height = 13
            Align = alBottom
            Caption = 'All of the clipped (actually removed from the plant)'
          end
          object suggest_clipping_button: TBitBtn
            Left = 366
            Top = 107
            Width = 175
            Height = 25
            Anchors = [akRight, akBottom]
            Caption = 'Enter suggested values'
            TabOrder = 0
            OnClick = suggest_clipping_buttonClick
            Glyph.Data = {
              76010000424D7601000000000000760000002800000020000000100000000100
              04000000000000010000120B0000120B00001000000000000000000000000000
              800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
              FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333393333
              333333333337F3333333333333397333333333333337FF333333333333C94333
              3333333333737F333333333333C9473333333333337373F3333333333CC94433
              3333333337F7F7F3333333333CC94473333333333737F73F33333333CCC94443
              333333337F37F37F33333333CCC94447333333337337F373F333333CCCC94444
              33333337F337F337F333333CCCC94444733333373337F3373F3333CCCCC94444
              4333337F3337FF337F3333CCCCC94444473333733F7773FF73F33CCCCC393444
              443337F37737F773F7F33CCC33393374447337F73337F33737FFCCC333393333
              444377733337F333777FC3333339333337437333333733333373}
            NumGlyphs = 2
          end
        end
        object last_clipping_tabsheet: TTabSheet
          Caption = 'Last clipping'
          ImageIndex = 2
          object Label4: TLabel
            Left = 0
            Top = 0
            Width = 541
            Height = 49
            Align = alTop
            AutoSize = False
            Caption = 
              'This option is used for crops with multiple other clipping event' +
              's.  One last clipping will be attempted on the scheduled date, h' +
              'arvest will occur only if there is sufficient biomass and the cr' +
              'op has not already entered dormancy.'
            Color = clInfoBk
            ParentColor = False
            WordWrap = True
          end
          object Label6: TLabel
            Left = 0
            Top = 49
            Width = 541
            Height = 49
            Align = alTop
            AutoSize = False
            Caption = 
              'Normally, with this mode, the crop will continue into dormancy a' +
              'nd restart in the spring.  Some times it may be appropriate to a' +
              'lso terminate the crop at this time  (I.e. to kill a perennial).' +
              '  In this case enable "Terminate crop".'
            Color = clInfoBk
            ParentColor = False
            WordWrap = True
          end
          object last_clipping_fate_label: TLabel
            Left = 0
            Top = 120
            Width = 234
            Height = 13
            Align = alBottom
            Caption = 'All of the clipped (actually removed from the plant)'
          end
          object suggest_last_clipping_button: TBitBtn
            Left = 366
            Top = 107
            Width = 175
            Height = 25
            Anchors = [akRight, akBottom]
            Caption = 'Enter suggested values'
            TabOrder = 0
            OnClick = suggest_last_clipping_buttonClick
            Glyph.Data = {
              76010000424D7601000000000000760000002800000020000000100000000100
              04000000000000010000120B0000120B00001000000000000000000000000000
              800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
              FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333393333
              333333333337F3333333333333397333333333333337FF333333333333C94333
              3333333333737F333333333333C9473333333333337373F3333333333CC94433
              3333333337F7F7F3333333333CC94473333333333737F73F33333333CCC94443
              333333337F37F37F33333333CCC94447333333337337F373F333333CCCC94444
              33333337F337F337F333333CCCC94444733333373337F3373F3333CCCCC94444
              4333337F3337FF337F3333CCCCC94444473333733F7773FF73F33CCCCC393444
              443337F37737F773F7F33CCC33393374447337F73337F33737FFCCC333393333
              444377733337F333777FC3333339333337437333333733333373}
            NumGlyphs = 2
          end
        end
        object grazing_tabsheet: TTabSheet
          Caption = 'Grazing'
          ImageIndex = 3
          object Label7: TLabel
            Left = 0
            Top = 0
            Width = 541
            Height = 17
            Align = alTop
            AutoSize = False
            Caption = 
              'This option is used for forage crops.  It activates the grazing ' +
              'submodel. '
            Color = clInfoBk
            ParentColor = False
            WordWrap = True
          end
          object Label18: TLabel
            Left = 0
            Top = 120
            Width = 257
            Height = 13
            Align = alBottom
            Caption = 'Including the percent biomass grazed specified above,'
          end
          object remove_for_grazing_edit: TAutoInt16EditBar
            Left = 0
            Top = 16
            Width = 541
            Height = 22
            Anchors = [akLeft, akTop, akRight]
            AutoScroll = False
            TabOrder = 0
            OnExit = update_total_percent
            Description_label = 'Consumed by animals'
            Units_label = '0-100%'
          end
          object grazing_groupbox: TGroupBox
            Left = 32
            Top = 58
            Width = 325
            Height = 64
            Anchors = [akLeft, akTop, akRight]
            Caption = 'Percent Nitrogen in produced manure (These must sum to 100%)'
            TabOrder = 2
            object grazing_OM_editbar: TAutoInt16EditBar
              Left = 2
              Top = 15
              Width = 321
              Height = 22
              Align = alTop
              AutoScroll = False
              TabOrder = 0
              OnExit = grazing_OM_editbar_onexit
              Description_label = 'from organic matter'
              Units_label = '0-100%'
            end
            object grazing_NH3_editbar: TAutoInt16EditBar
              Left = 2
              Top = 37
              Width = 321
              Height = 22
              Align = alTop
              AutoScroll = False
              TabOrder = 1
              OnExit = grazing_NH3_editbar_onexit
              Description_label = 'from ammonia (NH3)'
              Units_label = '0-100%'
            end
          end
          object biomass_returned_as_manure_editbar: TAutoInt16EditBar
            Left = 16
            Top = 36
            Width = 525
            Height = 22
            Hint = 
              'The portion of manure production actually deposited to the field' +
              ' soil surface as organic fertilizer (the remainder is loss)'
            Anchors = [akLeft, akTop, akRight]
            AutoScroll = False
            ParentShowHint = False
            ShowHint = True
            TabOrder = 1
            Description_label = 'Consumed biomass returned to the field as manure'
            Units_label = '0-100%'
          end
          object suggest_grazing_button: TBitBtn
            Left = 366
            Top = 107
            Width = 175
            Height = 25
            Anchors = [akRight, akBottom]
            Caption = 'Enter suggested values'
            TabOrder = 3
            OnClick = suggest_grazing_buttonClick
            Glyph.Data = {
              76010000424D7601000000000000760000002800000020000000100000000100
              04000000000000010000120B0000120B00001000000000000000000000000000
              800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
              FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333393333
              333333333337F3333333333333397333333333333337FF333333333333C94333
              3333333333737F333333333333C9473333333333337373F3333333333CC94433
              3333333337F7F7F3333333333CC94473333333333737F73F33333333CCC94443
              333333337F37F37F33333333CCC94447333333337337F373F333333CCCC94444
              33333337F337F337F333333CCCC94444733333373337F3373F3333CCCCC94444
              4333337F3337FF337F3333CCCCC94444473333733F7773FF73F33CCCCC393444
              443337F37737F773F7F33CCC33393374447337F73337F33737FFCCC333393333
              444377733337F333777FC3333339333337437333333733333373}
            NumGlyphs = 2
          end
        end
        object defoliation_tabsheet: TTabSheet
          Caption = 'Defoliation'
          ImageIndex = 4
          object Label8: TLabel
            Left = 0
            Top = 0
            Width = 541
            Height = 41
            Align = alTop
            AutoSize = False
            Caption = 
              'This option is used to remove most (or all) above ground biomass' +
              ',  biomatter may be removed, or usually it is applied to the soi' +
              'l surface and/or left as standing stubble, either allowing the c' +
              'rop to restart or terminate.'
            Color = clInfoBk
            ParentColor = False
            WordWrap = True
          end
          object Label19: TLabel
            Left = 0
            Top = 120
            Width = 80
            Height = 13
            Align = alBottom
            Caption = 'All above ground'
          end
          object suggest_defoliation_button: TBitBtn
            Left = 366
            Top = 107
            Width = 175
            Height = 25
            Anchors = [akRight, akBottom]
            Caption = 'Enter suggested values'
            TabOrder = 0
            OnClick = suggest_defoliation_buttonClick
            Glyph.Data = {
              76010000424D7601000000000000760000002800000020000000100000000100
              04000000000000010000120B0000120B00001000000000000000000000000000
              800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
              FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333393333
              333333333337F3333333333333397333333333333337FF333333333333C94333
              3333333333737F333333333333C9473333333333337373F3333333333CC94433
              3333333337F7F7F3333333333CC94473333333333737F73F33333333CCC94443
              333333337F37F37F33333333CCC94447333333337337F373F333333CCCC94444
              33333337F337F337F333333CCCC94444733333373337F3373F3333CCCCC94444
              4333337F3337FF337F3333CCCCC94444473333733F7773FF73F33CCCCC393444
              443337F37737F773F7F33CCC33393374447337F73337F33737FFCCC333393333
              444377733337F333777FC3333339333337437333333733333373}
            NumGlyphs = 2
          end
        end
      end
      object select_one_mode_memo: TMemo
        Left = 422
        Top = 8
        Width = 131
        Height = 33
        Anchors = [akTop, akRight]
        BorderStyle = bsNone
        Color = clAqua
        Lines.Strings = (
          '<-- Select one of these '
          'modes')
        TabOrder = 1
      end
      object biomatter_fate_groupbox: TGroupBox
        Left = 2
        Top = 179
        Width = 551
        Height = 128
        Align = alTop
        Caption = 'biomass has the following disposition '
        TabOrder = 2
        object ScrollBox1: TScrollBox
          Left = 2
          Top = 15
          Width = 547
          Height = 111
          Align = alClient
          BorderStyle = bsNone
          TabOrder = 0
          object remove_for_use_edit: TAutoInt16EditBar
            Left = 0
            Top = 0
            Width = 547
            Height = 22
            Hint = 
              'This accounts for biomatter that is removed from the field (in a' +
              'ddition to or in lieu of any harvest index yield) that may be co' +
              'nsumed for other purposes.'
            Align = alTop
            AutoScroll = False
            ParentShowHint = False
            ShowHint = True
            TabOrder = 0
            OnExit = update_total_percent
            Description_label = 
              'Removed and designated for beneficial use (clipped fodder, silag' +
              'e, etc.)'
            Units_label = '0-100%'
          end
          object remain_as_residue_edit: TAutoInt16EditBar
            Left = 0
            Top = 44
            Width = 547
            Height = 22
            Align = alTop
            AutoScroll = False
            TabOrder = 2
            OnExit = update_total_percent
            Description_label = 'Remains in the field laying as surface residue'
            Units_label = '0-100%'
          end
          object remove_for_disposal_edit: TAutoInt16EditBar
            Left = 0
            Top = 22
            Width = 547
            Height = 22
            Hint = 
              'This is used to account for biomatter that is not harvested yiel' +
              'd, otherwise consumed or applied to the soil), such as prunings,' +
              ' chaff or corn cobs that are collected but removed during proces' +
              'sing.'
            Align = alTop
            AutoScroll = False
            TabOrder = 1
            OnExit = update_total_percent
            Description_label = 'Removed from the field and disposed (unused)'
            Units_label = '0-100%'
          end
          object remain_as_standing_dead_edit: TAutoInt16EditBar
            Left = 0
            Top = 66
            Width = 547
            Height = 22
            Align = alTop
            AutoScroll = False
            TabOrder = 3
            OnExit = update_total_percent
            Description_label = 'Remains in the field as dead standing stubble/residue'
            Units_label = '0-100%'
          end
          object remain_as_standing_live_edit: TAutoInt16EditBar
            Left = 0
            Top = 88
            Width = 547
            Height = 22
            Hint = 
              'This reserves a portion of the plant as live and potentially reg' +
              'eneratable plant parts)'
            Align = alTop
            AutoScroll = False
            ParentShowHint = False
            ShowHint = True
            TabOrder = 4
            OnExit = update_total_percent
            Description_label = 'Remains as live standing plant tissue '
            Units_label = '0-100%'
          end
        end
      end
      object panel_biomass_fate_terminate_crop: TPanel
        Left = 2
        Top = 307
        Width = 551
        Height = 29
        Align = alTop
        BevelOuter = bvNone
        TabOrder = 3
        object Label11: TLabel
          Left = 444
          Top = 4
          Width = 8
          Height = 13
          Anchors = [akTop, akRight]
          Caption = '%'
        end
        object percent_total_out: TAutoInt16Edit
          Left = 377
          Top = 0
          Width = 54
          Height = 24
          Alignment = taRightJustify
          Anchors = [akTop, akRight]
          Color = clRed
          Lines.Strings = (
            '0')
          TabOrder = 0
          OnEnter = update_total_percent
        end
      end
    end
    object groupbox_clipping_required_conditions: TGroupBox
      Left = 0
      Top = 757
      Width = 555
      Height = 65
      Align = alTop
      Caption = 'Required conditions for Grazing/Clipping '
      TabOrder = 7
      object min_LAI_required_edit: TAutoFloat32EditBar
        Left = 2
        Top = 15
        Width = 551
        Height = 22
        Hint = 'This parameter is used for repeated clipping operations.'
        Align = alTop
        AutoScroll = False
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
        Description_label = 'Minimum LAI required for clipping'
        Units_label = 'm²/m²'
      end
      object min_biomass_required_edit: TAutoFloat32EditBar
        Left = 2
        Top = 37
        Width = 551
        Height = 22
        Hint = 'This parameter is used for repeated clipping operations.'
        Align = alTop
        AutoScroll = False
        ParentShowHint = False
        ShowHint = True
        TabOrder = 1
        Description_label = 'Minimum biomass required for clipping'
        Units_label = 'm²/m²'
      end
    end
  end
end
