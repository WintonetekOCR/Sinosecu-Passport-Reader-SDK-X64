object Form1: TForm1
  Left = 1189
  Top = 194
  Width = 672
  Height = 592
  Caption = #20013#23433#35777#20214#35782#21035#20363#31243
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object grp1: TGroupBox
    Left = 16
    Top = 8
    Width = 625
    Height = 345
    Caption = #25805#20316
    TabOrder = 0
    object grp2: TGroupBox
      Left = 16
      Top = 16
      Width = 265
      Height = 233
      Caption = #35782#21035#35843#29992#31243#24207
      TabOrder = 0
      object UserID: TEdit
        Left = 72
        Top = 32
        Width = 129
        Height = 21
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        TabOrder = 0
      end
      object edtCardType: TEdit
        Left = 80
        Top = 128
        Width = 121
        Height = 21
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        TabOrder = 1
      end
      object edtCardSize: TEdit
        Left = 80
        Top = 160
        Width = 121
        Height = 21
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        TabOrder = 2
      end
      object TStaticText
        Left = 24
        Top = 32
        Width = 39
        Height = 17
        Caption = #29992#25143'ID'
        TabOrder = 3
      end
      object txt3: TStaticText
        Left = 24
        Top = 136
        Width = 52
        Height = 17
        Caption = #35777#20214#31867#22411
        TabOrder = 4
      end
      object txt4: TStaticText
        Left = 24
        Top = 168
        Width = 52
        Height = 17
        Caption = #35777#20214#23610#23544
        TabOrder = 5
      end
      object btnLoad: TButton
        Left = 24
        Top = 88
        Width = 97
        Height = 25
        Caption = #21152#36733#35782#21035#26680#24515
        TabOrder = 6
        OnClick = btnLoadClick
      end
      object btnRecog: TButton
        Left = 80
        Top = 192
        Width = 75
        Height = 21
        Caption = #37319#38598#24182#35782#21035
        TabOrder = 7
        OnClick = btnRecogClick
      end
      object btnFree: TButton
        Left = 128
        Top = 88
        Width = 97
        Height = 25
        Caption = #37322#25918#35782#21035#26680#24515
        TabOrder = 8
        OnClick = btnFreeClick
      end
      object TStaticText
        Left = 24
        Top = 56
        Width = 41
        Height = 17
        Caption = 'DllPath:'
        TabOrder = 9
      end
      object Edit_DllPath: TEdit
        Left = 72
        Top = 56
        Width = 129
        Height = 21
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        TabOrder = 10
      end
    end
    object grp3: TGroupBox
      Left = 304
      Top = 24
      Width = 305
      Height = 233
      Caption = #33258#23450#20041#22270#20687#37319#38598#21442#25968#35774#32622
      TabOrder = 1
      object grp5: TGroupBox
        Left = 16
        Top = 24
        Width = 273
        Height = 105
        Caption = #35774#32622#33258#23450#20041#22270#20687#23485#39640
        TabOrder = 0
        object txt5: TStaticText
          Left = 24
          Top = 24
          Width = 40
          Height = 17
          Caption = #22270#20687#23485
          TabOrder = 0
        end
        object StaticText1: TStaticText
          Left = 24
          Top = 48
          Width = 40
          Height = 17
          Caption = #22270#20687#39640
          TabOrder = 1
        end
        object TBImageWidth: TEdit
          Left = 80
          Top = 24
          Width = 105
          Height = 21
          ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
          TabOrder = 2
        end
        object TBImageHeight: TEdit
          Left = 80
          Top = 48
          Width = 105
          Height = 21
          ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
          TabOrder = 3
        end
        object txt6: TStaticText
          Left = 192
          Top = 24
          Width = 56
          Height = 17
          Caption = #33521#23544'/1000'
          TabOrder = 4
        end
        object txt7: TStaticText
          Left = 192
          Top = 48
          Width = 56
          Height = 17
          Caption = #33521#23544'/1000'
          TabOrder = 5
        end
        object BtnSetImageWH: TButton
          Left = 32
          Top = 72
          Width = 164
          Height = 21
          Caption = #35774#32622#33258#23450#20041#37319#38598#23610#23544
          TabOrder = 6
          OnClick = BtnSetImageWHClick
        end
      end
      object grp6: TGroupBox
        Left = 16
        Top = 136
        Width = 273
        Height = 57
        Caption = #35774#32622#33258#23450#20041#37319#38598#20998#36776#29575
        TabOrder = 1
        object txt8: TStaticText
          Left = 8
          Top = 24
          Width = 40
          Height = 17
          Caption = #20998#36776#29575
          TabOrder = 0
        end
        object TBHoriResolution: TEdit
          Left = 56
          Top = 24
          Width = 57
          Height = 21
          ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
          TabOrder = 1
        end
        object txt10: TStaticText
          Left = 120
          Top = 24
          Width = 21
          Height = 17
          Caption = 'DPI'
          TabOrder = 2
        end
        object BtnSetAcquireImgResolution: TButton
          Left = 144
          Top = 24
          Width = 105
          Height = 21
          Caption = #35774#32622#37319#38598#20998#36776#29575
          TabOrder = 3
          OnClick = BtnSetAcquireImgResolutionClick
        end
      end
      object btnAcquireImage: TButton
        Left = 49
        Top = 200
        Width = 164
        Height = 21
        Caption = #33258#23450#20041#22270#20687#37319#38598
        TabOrder = 2
        OnClick = btnAcquireImageClick
      end
    end
  end
  object grp7: TGroupBox
    Left = 32
    Top = 272
    Width = 593
    Height = 65
    Caption = #20854#23427#25509#21475
    TabOrder = 1
    object BtnGetVersion: TButton
      Left = 16
      Top = 24
      Width = 124
      Height = 25
      Caption = #33719#21462#24403#21069#29256#26412#20449#24687
      TabOrder = 0
      OnClick = BtnGetVersionClick
    end
    object BtnGetDeviceName: TButton
      Left = 152
      Top = 24
      Width = 124
      Height = 25
      Caption = #33719#21462#35774#22791#21517#31216
      TabOrder = 1
      OnClick = BtnGetDeviceNameClick
    end
    object BtnCheckDeviceOnLine: TButton
      Left = 304
      Top = 24
      Width = 124
      Height = 25
      Caption = #26816#27979#35774#22791#29366#24577
      TabOrder = 2
      OnClick = btnGetDeviceStatusClick
    end
    object btnGetDeviceSN: TButton
      Left = 448
      Top = 24
      Width = 124
      Height = 25
      Caption = #33719#21462#35774#22791#24207#21015#21495
      TabOrder = 3
      OnClick = btnGetDeviceSNClick
    end
  end
  object edtTestResult: TMemo
    Left = 16
    Top = 369
    Width = 401
    Height = 169
    ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    Lines.Strings = (
      'edtTestResult')
    ScrollBars = ssVertical
    TabOrder = 2
  end
  object edtResultDescription: TMemo
    Left = 432
    Top = 369
    Width = 209
    Height = 169
    ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    Lines.Strings = (
      'edtTestResult')
    ScrollBars = ssVertical
    TabOrder = 3
  end
end
