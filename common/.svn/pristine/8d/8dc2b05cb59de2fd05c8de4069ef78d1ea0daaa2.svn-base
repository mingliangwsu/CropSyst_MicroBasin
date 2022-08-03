object geolocation_form: Tgeolocation_form
  Left = 2334
  Top = 210
  Width = 285
  Height = 226
  Align = alClient
  Caption = 'Geolocation'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object geolocation_pagecontrol: TPageControl
    Left = 0
    Top = 41
    Width = 277
    Height = 151
    Hint = 
      'Coordinates of the weather station may be entered in any one of ' +
      'these coordinate systems.  Entering values for one will automati' +
      'cally calculate the others.'
    ActivePage = tabsheet_position
    Align = alClient
    ParentShowHint = False
    ShowHint = True
    TabOrder = 0
    object tabsheet_position: TTabSheet
      Caption = 'Position'
      object coordinates_pagecontrol: TPageControl
        Left = 0
        Top = 0
        Width = 269
        Height = 81
        ActivePage = coord_UTM_tabsheet
        Align = alTop
        Style = tsButtons
        TabOrder = 0
        object tabsheet_coord_DMS: TTabSheet
          Caption = 'Degree-Min-Sec'
          object panel_latitude_DMS: TPanel
            Left = 0
            Top = 0
            Width = 261
            Height = 24
            Align = alTop
            Alignment = taLeftJustify
            BevelOuter = bvNone
            Caption = 'Latitude'
            TabOrder = 0
            object Label55: TLabel
              Left = 223
              Top = 0
              Width = 13
              Height = 24
              Align = alRight
              Caption = ' ° '
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clWindowText
              Font.Height = -16
              Font.Name = 'MS Sans Serif'
              Font.Style = []
              ParentFont = False
            end
            object Label56: TLabel
              Left = 236
              Top = 0
              Width = 11
              Height = 24
              Align = alRight
              Caption = ' '#39' '
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clWindowText
              Font.Height = -16
              Font.Name = 'MS Sans Serif'
              Font.Style = []
              ParentFont = False
            end
            object Label1: TLabel
              Left = 247
              Top = 0
              Width = 14
              Height = 24
              Align = alRight
              Caption = ' " '
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clWindowText
              Font.Height = -16
              Font.Name = 'MS Sans Serif'
              Font.Style = []
              ParentFont = False
            end
            object combobox_lat_dir: TComboBox
              Left = 202
              Top = 0
              Width = 59
              Height = 21
              ItemHeight = 13
              TabOrder = 0
              Text = 'North'
              OnExit = latitude_degminsec_onexit
              Items.Strings = (
                'South'
                'North')
            end
          end
          object panel_longitude_DMS: TPanel
            Left = 0
            Top = 24
            Width = 261
            Height = 24
            Align = alTop
            Alignment = taLeftJustify
            BevelOuter = bvNone
            Caption = 'Longitude'
            TabOrder = 1
            object Label58: TLabel
              Left = 223
              Top = 0
              Width = 13
              Height = 24
              Align = alRight
              Caption = ' ° '
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clWindowText
              Font.Height = -16
              Font.Name = 'MS Sans Serif'
              Font.Style = []
              ParentFont = False
            end
            object Label59: TLabel
              Left = 236
              Top = 0
              Width = 11
              Height = 24
              Align = alRight
              Caption = ' '#39' '
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clWindowText
              Font.Height = -16
              Font.Name = 'MS Sans Serif'
              Font.Style = []
              ParentFont = False
            end
            object Label60: TLabel
              Left = 247
              Top = 0
              Width = 14
              Height = 24
              Align = alRight
              Caption = ' " '
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clWindowText
              Font.Height = -16
              Font.Name = 'MS Sans Serif'
              Font.Style = []
              ParentFont = False
            end
            object combobox_long_dir: TComboBox
              Left = 202
              Top = 0
              Width = 59
              Height = 21
              ItemHeight = 13
              TabOrder = 0
              Text = 'West'
              OnExit = longitude_degmin_sec_onexit
              Items.Strings = (
                'West'
                'East')
            end
          end
        end
        object coord_dec_deg_tabsheet: TTabSheet
          Caption = 'Decimal degrees'
          ImageIndex = 1
          object panel_latitude_DD: TPanel
            Left = 0
            Top = 0
            Width = 261
            Height = 22
            Align = alTop
            Alignment = taLeftJustify
            BevelOuter = bvNone
            Caption = 'Latitude'
            TabOrder = 0
            object Label5: TLabel
              Left = 184
              Top = 0
              Width = 77
              Height = 13
              Align = alRight
              Caption = 'decimal degrees'
              Layout = tlCenter
            end
          end
          object panel_longitude_DD: TPanel
            Left = 0
            Top = 22
            Width = 261
            Height = 22
            Align = alTop
            Alignment = taLeftJustify
            BevelOuter = bvNone
            Caption = 'Longitude'
            TabOrder = 1
            object Label6: TLabel
              Left = 184
              Top = 0
              Width = 77
              Height = 13
              Align = alRight
              Caption = 'decimal degrees'
              Layout = tlCenter
            end
          end
        end
        object coord_UTM_tabsheet: TTabSheet
          Caption = 'UTM'
          ImageIndex = 2
          object panel_UTM_zone: TPanel
            Left = 0
            Top = 0
            Width = 86
            Height = 50
            Align = alLeft
            Alignment = taLeftJustify
            BevelOuter = bvNone
            Caption = '  Zone'
            TabOrder = 0
            object edit_UTM_zone_desg: TEdit
              Left = 39
              Top = 27
              Width = 17
              Height = 21
              MaxLength = 1
              TabOrder = 0
              Text = 'Z'
              OnChange = utm_onexit
            end
          end
          object panel_UTM_xxxing: TPanel
            Left = 86
            Top = 0
            Width = 175
            Height = 50
            Align = alClient
            BevelOuter = bvNone
            TabOrder = 1
            object panel_UTM_northing: TPanel
              Left = 0
              Top = 0
              Width = 175
              Height = 22
              Align = alTop
              Alignment = taLeftJustify
              BevelOuter = bvNone
              Caption = 'Northing'
              TabOrder = 0
              object utm_northing_units: TLabel
                Left = 167
                Top = 0
                Width = 8
                Height = 22
                Align = alRight
                Caption = 'm'
                Layout = tlCenter
              end
            end
            object panel_easting: TPanel
              Left = 0
              Top = 22
              Width = 175
              Height = 22
              Align = alTop
              Alignment = taLeftJustify
              BevelOuter = bvNone
              Caption = 'Easting'
              TabOrder = 1
              object Label3: TLabel
                Left = 167
                Top = 0
                Width = 8
                Height = 22
                Align = alRight
                Caption = 'm'
                Layout = tlCenter
              end
            end
          end
        end
      end
      object button_google_maps: TBitBtn
        Left = 163
        Top = 77
        Width = 104
        Height = 45
        Hint = 
          'Displays this location using Google Maps (Requires a Web browser' +
          ' and internet connection)'
        Anchors = [akTop, akRight]
        TabOrder = 1
        OnClick = button_google_mapsClick
        Glyph.Data = {
          AA120000424DAA12000000000000360400002800000064000000250000000100
          080000000000740E0000130B0000130B00000001000000010000CDEDF200CB58
          2300F6F6F600FCFCFC00FFFFFF00FAFAFA00FEFEFE00BCBBBC008D7871000318
          AE00F1F1F200692B0E00B3B3B40088381300A8451700EC8A5A00ABABAD00CDCE
          D000E1E1E100E5E5E600EEEEEE00DEDDDE00C9633400D4D3D300A2A2A300D36C
          3C00CECDCD00C1C1C10004B5E100F8F8F800D9855D00D9D9D900152CCC00B6B5
          B7009C401500C2C2C400B1B1B200DFDFE000F4F4F400A8A8A900E3E3E400B8B8
          BA00F0F0F000D0D0D000E7E7E700BFBFC000FDFDFD00D7D7D700C04F1A00FBFB
          FB0099989A00AE542A00ED986D00051DCA000282A200F4AA8400E2A688008481
          8700145B6D00CC521A00FDF5F00009156800A9786200F9EAE300D0D1D5000295
          BA00D6784D00C9C9CA00868C9700C1C5CE004358EF00B7AEAB0004ABD6000213
          8F00077C9900F5A37700EBEAEB00CACACC00D98F6D00DADADB0004C2F000B2B1
          B00003A0C700AD887700CBCBCD00C4C4C500CCCCCC009E9E9E00E6B19800E87D
          4A00C7C7C700EAEAEA00AFAFB0008F492900B54A1800172AB500F3F3F300374D
          E5009E908B0092909000F2D2C400F1C8B500DC5B1F00998B8500EBEBEC00ECEC
          EC006679FC00C8C8C8006B72A600DCDCDD006B433100E8E8E800C5C6C6005367
          F400018DB000E0723E0097695500A6A5A3007D56450039417C00B86F4E009BA8
          FD00ABEDF800A7ACBA007199A400CCCBCB006C6F8B00FEFAF90078655E005166
          7000FFFCFA002B3ECC001830DD00BFB9B7008D95D2004A539400DAD4D200F6DE
          D100046E8900CFB7AC00D5D5DA00EEBEA6003948B400293589009B5B3E008D59
          420015248E00AEB8FD0005620100A1A3B0002B41E300C49986006D889000D1C2
          BB0091A3B200FDF7F300FDFEFE00B0A19A00CDC5C200D0602C0054597E0006CC
          F900C6C4C400BDB7B50006D8FE002736AB00434FA400E9DDD800CBA997001651
          1300D7D1CE00C4C2C10061D35A00AEB1C7008B8EAE00C0C7FB00AA958D0096EB
          F800517D8900CED4FB0022C3EB00A7DBE400F4BB97000DF5FF00FCEFE9005966
          CA0091E18D004F93A400B4B7CF00497E4600A0C2CC00158E0E0095BD93007A87
          E200DDD8D600CBDEE10055CA4E00AD613F00ABBAAA0067ABBD00F5B38500C9C8
          C600DFDBD90089C3860027A220006CC1D70065B56100FEFDFD00DAFAFF00FAE5
          D7001F9A18004656C700F2FEFF001D6D1800F1F2FD00706D750081D47C0072CE
          E60049849300B0C5AF00E4E7FA002E592C0025738600616FD500DCDEEC00DAEF
          D900B8B9C3005863B50034ABC800F9FAFE0023859E006ECF68003FB93700CAD0
          CA0044A1B90078E9FE00A5ABD300ADB3D700E8662A00ECEBEB00A5CAA3002789
          23008B98EF0056C6E2003CA836005EFFFF00A2A7CA002CD6EE00B3C7D7002D64
          2900E3EDEE00E9EDE9009DA2C10042F5FF00D0C9C60043C13B00040404040404
          0404040404040404040404040404040404040404040404040404040404040404
          0404040404040404588D040404040404040404040404040368122B1A1A2B256F
          0506040404040404040404040404040404040404040404040404040404040404
          0404040404040404040404040404040404040404040404040404040404040404
          040404040404040404040404011E040404040404040404040404026F23211024
          0C210723252A0404040404040404040404040404040404040404040404040404
          0404040404040404040404040404040404040404040404040404040404040404
          040404040464643C420401041901191E0142011E046401012604040404022D67
          5D0E3B3B5E0E5307432912020404040404040404040404040404040404040404
          0404040404040404040404040404040404040404040404040404040404040404
          040404040404040404646465013C010401650158010158013F16658D34040404
          030A91220E309F424E0F015E2D1A1B2804040404040404040404040404040404
          0404040404040404040404040404040404040404040404040404040404040404
          040404040404040404040404046464424238010419010158011E041E048D0101
          8904040426785E0E9D0404040404040459221024050404040404040404040404
          0404040404040404040404040404040404040404040404040404040404040404
          0404040404040404040404040404040404646401381E0104A73F015801190419
          040158640404040499660E222604040404040404881639102604040404040404
          0404040404040404040404040404040404040404040404040404040404040404
          040404040404040404040404040404040404040404641E423C0101048D1E5804
          58641E58043F1E1E04040404A8340D801231040404040404044E0B6314040404
          0404040404040404040404040404040404040404040404040404040404040404
          0404040404040404040404040404040404040404040404040464013804420104
          040404040404040404040404040404048BC80D8054140404040404062C780B08
          2A04040404040404040404040404040404040404040404040404040404040404
          0404040405262C124F4F2512682A1D030404040404040404040404062E060404
          040404040404040404040404062E06040404040404B6166E51512F28140A4C4F
          C5300D6703040404040404040404040404042E2E2E0604040404040404040404
          04040404040403024F110721240C29075A561F120A022E040404040406032A68
          6F5B26050404040404040404040405264C6F682A03060404049B3433AB4D0723
          1A116B105E5E0DAB06063105310505030404040431026F132C681D2E04040404
          0404040404040404032A235C08765D6E5D5D91749D8554297510151D04042E02
          112D512917171B074F2A0404040404042A6DA3512D7D17431B1A022E04040489
          733074539D62220E300E150404036B0C240C70171D04055B071057575C24294D
          262E040404040404040404044C1767760D220E303B0119190133740839442B02
          0404606D183987876C441F1A211A310404040403172998B2DABB7B1A55241F0A
          04040404B8650F730E220E5E5E3304040414075732182F6F05062C1A39A08F77
          A0321A5A13020404040404040404032A080E0E5E3B16B8040404040404043819
          0B0B1726041D958F4909BC0204D6615F10101A140404261F367252C79C04D0EB
          3698180C020404040404030459665E5EEF040404042ABF9494BDDBE106268709
          09093520DF71096C051D0404040404040404261F0E0E5E5E970A040404040404
          0404580F0D0B17022E26090909A604040404D6713D39514F04042C7C41419A04
          04040404A13657182C0304040302251259012208030404040404E8BFF9290404
          031209093535F64C0404DCF20A0604040404040404069D305E5E339E04040404
          04042E03032E58340D0B4002028E3509951D040404040404613D325105044848
          72E631040404040403F73A81075B0405110C67324B1E762D6B2C04040404C4BF
          DD210304453535096C2E04040404040404040404040404040404333B5E0EA304
          040404040404052A281397340D0B542AAD350949251D040404040404715F8147
          60041C48367C82040404040404B54A3A51152E1462760D3037345D4710230504
          0404C4BFDD210304E33509092A040404040404040404040404040404041F3B30
          2291030404040404040469608C6B5359220B1A13618449926906040404040404
          6A613D391DC31C41B22F04040404040404C3488A571A603E0E0EB00404046516
          395717020404C4BFDD2103049620497E02030404040404040404040404040404
          04973B5E2227060404040404040458783E3E4E3701226005469649772A040404
          040404046A613D811DB51C72441504040404040404C3488A321A473B0E0E2606
          040404970BD71B4C0404C4BFDD2103044620492713280A050404040404040404
          0404040415663022676F04040404040404040404B8B8B8B8B83F3F046A614939
          260404040404040471963DA0057A4836101204040404040404B5483644127366
          0D080204040404AA5E0B21150404C4BFDD2103047120A0296813231B2F130506
          04040404040404048B665E220C68040404040404040404040404040404040404
          6A463D442604040404040404468449A09CB51C4A471504040404040404B54836
          32690F190D323104040404FE010B0C250404C4BFDD210304715F7E6C8E6C281F
          2D232514030404040404040497EE0E0D112A0404040404040404040404040404
          04040404C16A3D446F2E0404040404148435492704FA5036271A040404040404
          255052368C044B596E5C050404040453300D5A2A0404C4BFDD2103046A83392D
          04E571206C2157572B2A0404040404049759220D2B0A04040404040404040404
          0404040404040404EC6A3D392F02040404042EBC35098F150482A47257073104
          0404049CF85041360A0438346E102A04040413165E0D121D0404C4BFDD210304
          6A6139211D0404B32049D7635A140404040404048B4B220B4314040404040404
          04040404040404040404040404938377241B690202149535090969040404F5A4
          982D4D12021D0A6F1C48417C06049B4B5D211B17281FC53B225D28140604C4BF
          DD210304B36A772D5A1202604D96493D022E0404040404049937220B2D5B0404
          040404040404040404040404040404040404715FAA074317171AA53535090404
          0404D4FD4A2D29552F6D25451C48BB60040404D1190811705A235E5E0D621B17
          1D04C4BFDD21030404795F95071B17116C84099204040404040404040238330B
          24400404040404040404040404040404040404040404049320875411AEA58484
          8C04040404040404EB507C235654F3501CC70404040404049BB6337816420F42
          905D51690504ACBFDD0C3104040493616CE27BE38484FC040404041818040404
          04A8190B75232E0404040404040404040404062E04040404040404047946205F
          9661B9ED040404040404040404D0B448521CA1B48C0404040404040404046437
          4B37374B594278A80604ACBFDD0C3104040404DC6120836161DF0404049C0418
          18040404049C4B33D7276F030404040404040404040402152802040404040404
          0404040404040404040404040404040404040404040404040404040404040404
          0404040404040404040404040404ACD2DD240504040404040404040404040404
          040404040404040404044B596E18561404040404040404040404022F1B250604
          0404040404040404040404040404040404040404040404040404040404040404
          040404040404040404040404040404040404ACD2DD1005040404040404040404
          040404040404040404040404040482C8330B275C2C02040404040404052A080D
          5718690304040404040404040404040404040404040404040404040404040404
          04040404040404040404040404040404040404040404ACCCA927020404040404
          040404040404040404040404040404040404043C0F335C241B2F0A1D03030502
          252B740D8029142E040404040404040404040404040404040404040404040404
          0404040404040404040404040404040404040404040404040404ACCCA9180204
          0404040404040404040404040404040404040404040404048265165D43560707
          2D2D2D07080E3B30225304040404040404040404040404040404040404040404
          040404040404040404040404040404040404040404040404040404040260C4CC
          A9634C0304040404040404040404040404040404040404040404040404043773
          90677D2B43709D08300166011704040404040404040404040404040404040404
          0404040404040404040404040404040404040404040404040404040404040404
          0360FFD2A9632502040404040404040404040404040404040404040404040404
          040404043C641E190133421E8BA7040404040404040404040404040404040404
          0404040404040404040404040404040404040404040404040404040404040404
          04040404D8C4BAACBFBD02310404040404040404040404040404040404040404
          0404040404040404040404049B3C040404040404040404040404040404040404
          0404040404040404040404040404040404040404040404040404040404040404
          040404040404040404E1BABACECE050404040404040404040404040404040404
          0404040404040404040404040404040404040404040404040404040404040404
          0404040404040404040404040404040404040404040404040404040404040404
          0404040404040404040404040404040404040404040404040404040404040404
          0404040404040404040404040404040404040404040404040404040404040404
          0404040404040404040404040404040404040404040404040404040404040404
          0404040404040404040404040404040404040404040404040404040404040404
          0404040404040404040404040404040404040404040404040404040404040404
          0404040404040404040404040404040404040404040404040404040404040404
          0404040404040404040404040404040404040404040404040404040404040404
          0404040404040404040404040404}
      end
      object panel_heights: TPanel
        Left = 0
        Top = 81
        Width = 157
        Height = 42
        Align = alLeft
        BevelOuter = bvNone
        TabOrder = 2
        object panel_elevation: TPanel
          Left = 0
          Top = 0
          Width = 157
          Height = 22
          Align = alTop
          Alignment = taLeftJustify
          BevelOuter = bvNone
          Caption = 'Elevation'
          TabOrder = 0
          object Label8: TLabel
            Left = 149
            Top = 0
            Width = 8
            Height = 22
            Align = alRight
            Caption = 'm'
            Layout = tlCenter
          end
        end
        object panel_screening_height: TPanel
          Left = 0
          Top = 22
          Width = 157
          Height = 22
          Align = alTop
          Alignment = taLeftJustify
          BevelOuter = bvNone
          Caption = 'Screening height'
          TabOrder = 1
          object Label9: TLabel
            Left = 149
            Top = 0
            Width = 8
            Height = 22
            Align = alRight
            Caption = 'm'
            Layout = tlCenter
          end
        end
      end
    end
    object tabsheet_region: TTabSheet
      Hint = 
        'This information is not used by CropSyst or ClimGen, but if ofte' +
        'n imported by the weather format import utilities.  It is recomm' +
        'ended to provide this data to adequately document the weather da' +
        'ta.'
      Caption = 'Region'
      ImageIndex = 1
      ParentShowHint = False
      ShowHint = True
      object scrollbox_region: TScrollBox
        Left = 0
        Top = 0
        Width = 269
        Height = 123
        Align = alClient
        TabOrder = 0
        object groupbox_country: TGroupBox
          Left = 0
          Top = 0
          Width = 248
          Height = 63
          Align = alTop
          Caption = 'Country'
          TabOrder = 0
          object combobox_country_ISO3166_code: TComboBox
            Left = 2
            Top = 15
            Width = 244
            Height = 22
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Courier New'
            Font.Style = []
            ItemHeight = 14
            ParentFont = False
            TabOrder = 0
            Text = '  0  (Unknown) '
            OnChange = country_ISO3166_code_combobox_onchange
            Items.Strings = (
              '  0  (Unknown) '
              '840  United States'
              '  4  Afghanistan'
              '  8  Albania'
              ' 12  Algeria'
              ' 16  American Samoa'
              ' 20  Andorra'
              ' 24  Angola'
              '660  Anguilla'
              ' 10  Antarctica'
              ' 28  Antigua and Barbuda'
              ' 32  Argentina'
              ' 51  Armenia'
              '533  Aruba'
              ' 36  Australia'
              ' 40  Austria'
              ' 31  Azerbaijan'
              ' 44  Bahamas'
              ' 48  Bahrain'
              ' 50  Bangladesh'
              ' 52  Barbados'
              '112  Belarus'
              ' 56  Belgium'
              ' 84  Belize'
              '204  Benin'
              ' 60  Bermuda'
              ' 64  Bhutan'
              ' 68  Bolivia'
              ' 70  Bosnia and Herzegowina'
              ' 72  Botswana'
              ' 74  Bouvet Island'
              ' 76  Brazil'
              ' 86  British Indian Ocean Territory'
              ' 96  Brunei Darussalam'
              '100  Bulgaria'
              '854  Burkina Faso'
              '108  Burundi'
              '116  Cambodia'
              '120  Cameroon'
              '124  Canada'
              '132  Cape Verde'
              '136  Cayman Islands'
              '140  Central African Republic'
              '148  Chad'
              '152  Chile'
              '156  China'
              '162  Christmas Island'
              '166  Cocos (Keeling) Islands'
              '170  Colombia'
              '174  Comoros'
              '178  Congo'
              '180  Congo, The Democratic Republic Of The'
              '184  Cook Islands'
              '188  Costa Rica'
              '384  Cote D'#39'Ivoire'
              '191  Croatia (Local Name: Hrvatska)'
              '192  Cuba'
              '196  Cyprus'
              '203  Czech Republic'
              '208  Denmark'
              '262  Djibouti'
              '212  Dominica'
              '214  Dominican Republic'
              '626  East Timor'
              '218  Ecuador'
              '818  Egypt'
              '222  El Salvador'
              '226  Equatorial Guinea'
              '232  Eritrea'
              '233  Estonia'
              '231  Ethiopia'
              '238  Falkland Islands (Malvinas)'
              '234  Faroe Islands'
              '242  Fiji'
              '246  Finland'
              '250  France'
              '249  France, Metropolitan'
              '254  French Guiana'
              '258  French Polynesia'
              '260  French Southern Territories'
              '266  Gabon'
              '270  Gambia'
              '268  Georgia'
              '276  Germany'
              '288  Ghana'
              '292  Gibraltar'
              '300  Greece'
              '304  Greenland'
              '308  Grenada'
              '312  Guadeloupe'
              '316  Guam'
              '320  Guatemala'
              '324  Guinea'
              '624  Guinea-Bissau'
              '328  Guyana'
              '332  Haiti'
              '334  Heard and Mc Donald Islands'
              '336  Holy See (Vatican City State)'
              '340  Honduras'
              '344  Hong Kong'
              '348  Hungary'
              '352  Iceland'
              '356  India'
              '360  Indonesia'
              '364  Iran (Islamic Republic Of)'
              '368  Iraq'
              '372  Ireland'
              '376  Israel'
              '380  Italy'
              '388  Jamaica'
              '392  Japan'
              '400  Jordan'
              '398  Kazakhstan'
              '404  Kenya'
              '296  Kiribati'
              '408  Korea, Democratic People'#39'S Republic Of'
              '410  Korea, Republic Of'
              '414  Kuwait'
              '417  Kyrgyzstan'
              '418  Lao People'#39'S Democratic Republic'
              '428  Latvia'
              '422  Lebanon'
              '426  Lesotho'
              '430  Liberia'
              '434  Libyan Arab Jamahiriya'
              '438  Liechtenstein'
              '440  Lithuania'
              '442  Luxembourg'
              '446  Macau'
              '807  Macedonia, The Former Yugoslav Republic Of'
              '450  Madagascar'
              '454  Malawi'
              '458  Malaysia'
              '462  Maldives'
              '466  Mali'
              '470  Malta'
              '584  Marshall Islands'
              '474  Martinique'
              '478  Mauritania'
              '480  Mauritius'
              '175  Mayotte'
              '484  Mexico'
              '583  Micronesia, Federated States Of'
              '498  Moldova, Republic Of'
              '492  Monaco'
              '496  Mongolia'
              '500  Montserrat'
              '504  Morocco'
              '508  Mozambique'
              '104  Myanmar'
              '516  Namibia'
              '520  Nauru'
              '524  Nepal'
              '528  Netherlands'
              '530  Netherlands Antilles'
              '540  New Caledonia'
              '554  New Zealand'
              '558  Nicaragua'
              '562  Niger'
              '566  Nigeria'
              '570  Niue'
              '574  Norfolk Island'
              '580  Northern Mariana Islands'
              '578  Norway'
              '512  Oman'
              '586  Pakistan'
              '585  Palau'
              '591  Panama'
              '598  Papua New Guinea'
              '600  Paraguay'
              '604  Peru'
              '608  Philippines'
              '612  Pitcairn'
              '616  Poland'
              '620  Portugal'
              '630  Puerto Rico'
              '634  Qatar'
              '638  Reunion'
              '642  Romania'
              '643  Russian Federation'
              '646  Rwanda'
              '659  Saint Kitts and Nevis'
              '662  Saint Lucia'
              '670  Saint Vincent and The Grenadines'
              '882  Samoa'
              '674  San Marino'
              '678  Sao Tome and Principe'
              '682  Saudi Arabia'
              '686  Senegal'
              '690  Seychelles'
              '694  Sierra Leone'
              '702  Singapore'
              '703  Slovakia (Slovak Republic)'
              '705  Slovenia'
              ' 90  Solomon Islands'
              '706  Somalia'
              '710  South Africa'
              '239  South Georgia and The South Sandwich Islands'
              '724  Spain'
              '144  Sri Lanka'
              '654  St. Helena'
              '666  St. Pierre and Miquelon'
              '736  Sudan'
              '740  Suriname'
              '744  Svalbard and Jan Mayen Islands'
              '748  Swaziland'
              '752  Sweden'
              '756  Switzerland'
              '760  Syrian Arab Republic'
              '158  Taiwan, Province Of China'
              '762  Tajikistan'
              '834  Tanzania, United Republic Of'
              '764  Thailand'
              '768  Togo'
              '772  Tokelau'
              '776  Tonga'
              '780  Trinidad and Tobago'
              '788  Tunisia'
              '792  Turkey'
              '795  Turkmenistan'
              '796  Turks and Caicos Islands'
              '798  Tuvalu'
              '800  Uganda'
              '804  Ukraine'
              '784  United Arab Emirates'
              '826  United Kingdom'
              '840  United States'
              '581  United States Minor Outlying Islands'
              '858  Uruguay'
              '860  Uzbekistan'
              '548  Vanuatu'
              '862  Venezuela'
              '704  Viet Nam'
              ' 92  Virgin Islands (British)'
              '850  Virgin Islands (U.S.)'
              '876  Wallis and Futuna Islands'
              '732  Western Sahara'
              '887  Yemen'
              '891  Yugoslavia'
              '894  Zambia'
              '716  Zimbabwe')
          end
        end
        object groupbox_state_province: TGroupBox
          Left = 0
          Top = 63
          Width = 248
          Height = 63
          Align = alTop
          Caption = 'State/Province'
          TabOrder = 1
          object combobox_US_state_FIPS: TComboBox
            Left = 2
            Top = 15
            Width = 244
            Height = 22
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Courier New'
            Font.Style = []
            ItemHeight = 14
            ParentFont = False
            TabOrder = 0
            Text = ' 0 (Unknown)'
            OnChange = US_state_FIPS_combobox_onchange
            Items.Strings = (
              ' 0 (Unknown)'
              ' 2  Alaska'
              ' 1  Alabama'
              ' 5  Arkansas'
              '60  American Samoa'
              ' 4  Arizona'
              ' 6  California'
              ' 8  Colorado'
              ' 9  Connecticut'
              '11  District Of Columbia'
              '10  Delaware'
              '12  Florida'
              '13  Georgia'
              '66  Guam'
              '15  Hawaii'
              '19  Iowa'
              '16  Idaho'
              '17  Illinois'
              '18  Indiana'
              '20  Kansas'
              '21  Kentucky'
              '22  Louisiana'
              '25  Massachusetts'
              '24  Maryland'
              '23  Maine'
              '26  Michigan'
              '27  Minnesota'
              '29  Missouri'
              '28  Mississippi'
              '30  Montana'
              '37  North Carolina'
              '38  North Dakota'
              '31  Nebraska'
              '33  New Hampshire'
              '34  New Jersey'
              '35  New Mexico'
              '32  Nevada'
              '36  New York'
              '39  Ohio'
              '40  Oklahoma'
              '41  Oregon'
              '42  Pennsylvania'
              '72  Puerto Rico'
              '44  Rhode Island'
              '45  South Carolina'
              '46  South Dakota'
              '47  Tennessee'
              '48  Texas'
              '49  Utah'
              '51  Virginia'
              '78  Virgin Islands'
              '50  Vermont'
              '53  Washington'
              '55  Wisconsin'
              '54  West Virginia'
              '56  Wyoming')
          end
        end
        object groupbox_region: TGroupBox
          Left = 0
          Top = 126
          Width = 248
          Height = 66
          Align = alTop
          Caption = 'County/Region'
          TabOrder = 2
          object combobox_county_code: TComboBox
            Left = 2
            Top = 15
            Width = 244
            Height = 22
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Courier New'
            Font.Style = []
            ItemHeight = 0
            ParentFont = False
            TabOrder = 0
            Text = 'County code not yet implemented'
            Visible = False
          end
        end
      end
    end
    object tabsheet_station: TTabSheet
      Hint = 
        'This information is not used by CropSyst or ClimGen, but if ofte' +
        'n imported by the weather format import utilities.  It is recomm' +
        'ended to provide this data to adequately document the weather da' +
        'ta source'
      Caption = 'Weather station'
      ImageIndex = 2
      ParentShowHint = False
      ShowHint = True
      object groupbox_station_number: TGroupBox
        Left = 0
        Top = 0
        Width = 269
        Height = 41
        Align = alTop
        Caption = 'Number'
        TabOrder = 0
        object edit_station_number: TEdit
          Left = 2
          Top = 15
          Width = 265
          Height = 24
          TabOrder = 0
          Text = '0'
          OnChange = station_number_edit_onchange
        end
      end
      object groupbox_station_ID_code: TGroupBox
        Left = 0
        Top = 41
        Width = 269
        Height = 41
        Align = alTop
        Caption = 'Identification code'
        TabOrder = 1
      end
      object goupbox_station_name: TGroupBox
        Left = 0
        Top = 82
        Width = 269
        Height = 41
        Align = alClient
        Caption = 'Name'
        TabOrder = 2
      end
    end
  end
  object groupbox_description: TGroupBox
    Left = 0
    Top = 0
    Width = 277
    Height = 41
    Align = alTop
    Caption = 'Description of the location or weather station'
    TabOrder = 1
  end
end
