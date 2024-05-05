unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ExtCtrls;

type
  TForm1 = class(TForm)
    grp1: TGroupBox;
    grp2: TGroupBox;
    UserID: TEdit;
    edtCardType: TEdit;
    edtCardSize: TEdit;
    txt3: TStaticText;
    txt4: TStaticText;
    btnLoad: TButton;
    btnRecog: TButton;
    btnFree: TButton;
    grp3: TGroupBox;
    grp5: TGroupBox;
    txt5: TStaticText;
    StaticText1: TStaticText;
    TBImageWidth: TEdit;
    TBImageHeight: TEdit;
    txt6: TStaticText;
    txt7: TStaticText;
    BtnSetImageWH: TButton;
    grp6: TGroupBox;
    txt8: TStaticText;
    TBHoriResolution: TEdit;
    txt10: TStaticText;
    BtnSetAcquireImgResolution: TButton;
    grp7: TGroupBox;
    BtnGetVersion: TButton;
    BtnGetDeviceName: TButton;
    BtnCheckDeviceOnline: TButton;
    edtTestResult: TMemo;
    btnAcquireImage: TButton;
    btnGetDeviceSN: TButton;
    Edit_DllPath: TEdit;
    edtResultDescription: TMemo;
    //procedure btneClick(Sender: TObject);
    procedure btnFreeClick(Sender: TObject);
    procedure btnRecogClick(Sender: TObject);
    procedure btnLoadClick(Sender: TObject);
    procedure BtnSetImageWHClick(Sender: TObject);
    procedure BtnSetAcquireImgResolutionClick(Sender: TObject);
    procedure BtnGetVersionClick(Sender: TObject);
    procedure BtnGetDeviceNameClick(Sender: TObject);
    procedure btnGetDeviceSNClick(Sender: TObject);
    procedure btnGetDeviceStatusClick(Sender: TObject);
	procedure FormCreate(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure btnAcquireImageClick(Sender: TObject);

  private
    { Private declarations }
//��ʼ��
	InitIDCard:function(lpUserId: PWideChar; nType: Integer; lpDirectory: PWideChar):Longint;stdcall;
	FreeIDCard:procedure();stdcall ;
//����豸״̬
	CheckDeviceOnlineEx:function():Boolean; stdcall; 
//�趨�ɼ�����
	AcquireImage:function(nImageSizeType: integer):Longint;stdcall;
	SetAcquireImageType:function(nLightType: Integer; nImageType: Integer):Boolean; stdcall; 
	SetUserDefinedImageSize:function(nWidth: Integer; nHeight: Integer): Boolean; stdcall; 
	SetAcquireImageResolution:function(nResolutionX: Integer; nResolutionY: Integer):Boolean; stdcall; 
//�趨֤������
	ResetIDCardID:function(): Integer; stdcall;
	AddIDCardID:function(nMainID: integer; nSubID:PInteger  ; nSubIDCount: integer): Integer; stdcall;
	SetIDCardRejectType:function(nMainID: integer; bFlag:BOOL): Integer; stdcall; 
//֤��ʶ��
	RecogIDCard:function(): integer; stdcall; 
	RecogIDCardEX:function(nMainID:Integer;nSubID:Integer): Integer; stdcall; 
	GetRecogResult:function(nIndex: integer; lBuffer: PWideChar; nBufferLen: PInteger): integer; stdcall; 
	GetFieldName:function(nIndex: integer; lBuffer: PWideChar; nBufferLen: PInteger): integer; stdcall; 
	GetResultType:function(nIndex: integer): integer; stdcall; 
	GetIDCardName:function(lBuffer: PWideChar; nBufferLen: PInteger): integer; stdcall; 
	GetSubID:function(): integer; stdcall; 
//ʶ��󱣴�ͼ��
	SaveImage:function(lpPath:PWideChar):Integer; stdcall;
	SaveHeadImage:function(lpPath:PWideChar):Integer; stdcall;
//��Ƭ�ӿ�
	RecogBusinessCard:function(nCardType:Integer):Integer;stdcall;
	GetBusinessCardResultCount:function(nID:Integer):Integer;stdcall;
	GetBusinessCardResult:function(nID:Integer;nIndex:Integer ;lpBuffer:PWideChar;nBufferLen:PInteger):Integer;stdcall; 
	GetBusinessCardFieldName:function(nID:Integer;lpBuffer:PWideChar;nBufferLen:PInteger):Integer;stdcall;
	GetBusinessCardPosition:function( nID:Integer;nIndex:Integer;nLen:PInteger;nRight:PInteger;nTop:Pinteger;nBottom:Integer):Integer;stdcall;
//�����ӿ�
	GetVersionInfo:function(lpDeviceInfo: PWideChar; nBuffLen: Integer):Boolean;stdcall; 
	GetCurrentDevice:function(lpDeviceName: PWideChar; nBuffLength: Integer):Boolean; stdcall; 
	GetDeviceSN:function(lpDeviceSN: PWideChar; nBuffLength: Integer):Integer; stdcall; 
	CheckDeviceSI:function(lpDeviceSI: PWideChar; nBuffLength: Integer):Integer; stdcall; 
	WriteDeviceSI:function(lpDeviceSI: PWideChar; nBuffLength: Integer):Integer; stdcall; 

  public
    { Public declarations }
	  procedure GetBussinessCardContent;
  end;

var
	Form1: TForm1;
	bLoaded : Boolean ;
	Mutex:Boolean;
  
implementation

{$R *.dfm}


procedure TForm1.FormCreate(Sender:TObject);
begin
	edtResultDescription.Text := '��ȡ�ֶν��������'+ #13#10+ #13#10;
	edtResultDescription.Text := edtResultDescription.Text + '0-������ȡ' + #13#10+ #13#10;
	edtResultDescription.Text := edtResultDescription.Text + '1-�Ӷ���OCR��ȡ' + #13#10+ #13#10;
	edtResultDescription.Text := edtResultDescription.Text + '2-������ʶ�𵼳�' + #13#10+ #13#10;
  edtResultDescription.Text := edtResultDescription.Text + '3-������OCR��ȡ' + #13#10+ #13#10;
  edtResultDescription.Text := edtResultDescription.Text + '4-�Ӷ���ʶ�𵼳�' + #13#10+ #13#10;

  Edit_DllPath.Text:='..\..\..\..\lib';
end;

procedure TForm1.btnFreeClick(Sender: TObject);
begin
    FreeIDCard();
    edtTestResult.Text :='�ͷź��ĳɹ���';
    bLoaded:=False ;
end;

procedure TForm1.btnRecogClick(Sender: TObject);
var
  i:Integer ;
  nRet:Integer ;
  nCardType:Integer ;
  nCardSize:Integer;
  pResult:PWideChar;
  pField:PWideChar;
  pCardName:PWideChar;
  nResultType:Integer;
  strpResult:String;
  strpField:String;
  nSubId:array[0..1] of Integer  ;
  strtmp:String;
  nSize:Integer;
  strPath:String;
  pPath:PWideChar;
begin
    if bLoaded =False then
    begin
		  edtTestResult.Text:='ʶ�����δ���أ�';
      Exit;
    end;
    Mutex:=True;
    strpResult:=edtCardType.Text ;
    strpField:=edtCardSize.Text ;
    if Length(strpResult)=0 then
    begin
      edtTestResult.Text:='������֤�����͡��ߴ磡';
    Exit;
    end;
    if Length(strpResult)=0 then
    begin
      edtTestResult.Text:='������֤�����͡��ߴ磡';
    Exit;
    end;
    nCardType:=StrToInt(strpResult);
    nCardSize:=StrToInt(strpField);
    nSubId[0]:=0;
    nSubId[1]:=0;

    nRet := AcquireImage(nCardSize);
    if nRet=0 then
    begin
      edtTestResult.Text:=edtTestResult.Text + 'ͼ��ɼ��ɹ���';
    end
    else
    begin
      edtTestResult.Text:= edtTestResult.Text + 'ͼ��ɼ�ʧ�ܡ����� ' + IntToStr(nRet);
    end;
    strPath:='C:/images/test.jpg';
    GetMem(pPath, (Length(strPath)+1) * Sizeof(WideChar));
    StringToWideChar(strPath, pPath, (Length(strPath)+1) * Sizeof(WideChar));
    nRet := SaveImage(pPath);
    if nRet=0 then
    begin
      edtTestResult.Text:=edtTestResult.Text + 'ͼ�񱣴�ɹ���';
    end
    else
    begin
      edtTestResult.Text:= edtTestResult.Text + 'ͼ�񱣴�ʧ�ܡ����� ' + IntToStr(nRet);
    end;
    //��Ƭ��ʶ��
    if nCarDType=1010 Then
    begin
      nRet := RecogBusinessCard(1);
      if nRet=0 Then
      begin
        edtTestResult.Text := edtTestResult.Text + 'ʶ��ɹ���';
        GetBussinessCardContent();
      end
      else
      begin
        edtTestResult.Text := edtTestResult.Text + 'ʶ��ʧ�ܣ����� ' + IntToStr(nRet);
        Exit;
      end;
    end;
    //֤����ʶ��
    ResetIDCardID();
    AddIDCardID(nCardType,@nSubId,2);
    //ʶ��ǰ���þ�ʶ֤������
    SetIDCardRejectType(nCardType,True);
    nRet:=RecogIDCard();
    //nRet:=RecogIDCardEx(nCardType,0);
    if nRet = 0 then
    begin
        edtTestResult.Text:='ʶ��ʧ�ܣ����� ' + IntToStr(nRet);
        Exit;
    end;
    nSize:=128;
    GetMem(pResult, (128) * Sizeof(WideChar));
    GetMem(pField , (128) * Sizeof(WideChar));
    GetMem(pCardName , (128) * Sizeof(WideChar));
    i:=0;
    edtTestResult.Text:='';
    strtmp:='';
    // ʶ��ɹ�����ȡ֤����
    GetIDCardName(pCardName,@nsize);
    strtmp := strtmp + '֤����:';
    strtmp := strtmp + pCardName + #13#10;
    // ��ȡ֤��������
    strtmp := strtmp + 'SubID:' + IntToStr(GetSubID()) + #13#10;
    while 1=1 do
    begin
        nRet:=GetRecogResult(i,pResult,@nsize);
        if nRet=3 then
        begin
            Exit;
        end;
        GetFieldName(i,pField,@nSize);
		    nResultType := GetResultType(i);
	      strtmp:=strtmp+pField;
        strtmp:=strtmp+'(';
	      strtmp:=strtmp+IntToStr(nResultType);
	      strtmp:=strtmp+')';
        strtmp:=strtmp+':';
        strtmp:=strtmp+pResult;
        strtmp:=strtmp+'  ';
        strtmp:=strtmp+#13#10;
        edtTestResult .Text:=strtmp;

        i:=i+1;
    end;
    Mutex:=False;
end;


procedure TForm1.GetBussinessCardContent;
var
	nRet : Integer;
	nCount:Integer;
	i : Integer;
	pFieldValue : PWideChar;
	pFieldName : PWideChar ;
	nIndex : Integer;
	nSize : Integer;
	strtmp : String;
begin
	nIndex := 0;
	nCount := 0;
	i := 0;
	nSize := 128;
	strtmp := '';
	GetMem(pFieldName, (128) * Sizeof(WideChar));
	GetMem(pFieldValue , (128) * Sizeof(WideChar));

	while 1 = 1 do
	begin
		nSize := 128;
		strtmp := '';
		ZeroMemory(pFieldName, (128) * Sizeof(WideChar));
		ZeroMemory(pFieldValue, (128) * Sizeof(WideChar));
		
		nRet := GetBusinessCardFieldName(nIndex, pFieldValue, @nSize);
		if nRet >0 then
		begin
			nCount := GetBusinessCardResultCount(nIndex);
			if nCount = 0 then
			begin
				strtmp := strtmp + pFieldName + ':' + ' ' + #13#10;
			end;
			
			for i := 0 to nCount do
			begin
				GetBusinessCardResult(nIndex,i,pFieldValue,@nSize);
				strtmp := strtmp + pFieldName + ':' + pFieldValue + ' ' + #13#10;
			end;
		end
		else
			Exit;
		strtmp := strtmp + pFieldName + ':' + pFieldValue + ' ' + #13#10;
		edtTestResult.Text := edtTestResult.Text + strtmp;
		nIndex := nIndex + 1;
	end;
	
end;


procedure TForm1.btnLoadClick(Sender: TObject);
var
  ret :Longint;
  strCode:String;
  pCode:PWideChar;

  curDllDirectory:String;
  pDllDirectory:PWideChar; 
  
  curDllPath:String;
  pDllPath:PWideChar;
  myLibHandle:THandle;
begin
  Mutex:=True;
  curDllDirectory:=Edit_DllPath.Text;
  GetMem(pDllDirectory,(Length(curDllDirectory)+1)*Sizeof(WideChar));
  StringToWideChar(curDllDirectory,pDllDirectory,(Length(curDllDirectory)+1)*Sizeof(WideChar));

//  if Length(curDllDirectory)=0 then
//  begin
//    curDllPath:='IDCard.dll';
//  end
//  else
//  begin
//    curDllPath:=curDllDirectory+'\IDCard.dll';
//  end;
  curDllPath:=curDllDirectory+'\IDCard.dll';
  GetMem(pDllPath,(Length(curDllPath)+1)*Sizeof(WideChar));
  StringToWideChar(curDllPath,pDllPath,(Length(curDllPath)+1)*Sizeof(WideChar));
  myLibHandle:=LoadLibraryEx(PChar(curDllPath),0,LOAD_WITH_ALTERED_SEARCH_PATH);
  if myLibHandle>0then
  begin
    @InitIDCard := GetProcAddress(myLibHandle, PChar('InitIDCard'));
    @FreeIDCard := GetProcAddress(myLibHandle, PChar('FreeIDCard'));
    
    @AcquireImage := GetProcAddress(myLibHandle, PChar('AcquireImage'));
    @SetAcquireImageResolution := GetProcAddress(myLibHandle, PChar('SetAcquireImageResolution'));
    @SetAcquireImageType := GetProcAddress(myLibHandle, PChar('SetAcquireImageType'));
    @SetUserDefinedImageSize := GetProcAddress(myLibHandle, PChar('SetUserDefinedImageSize'));
	
    @CheckDeviceOnlineEx := GetProcAddress(myLibHandle, PChar('CheckDeviceOnlineEx'));
	
    @ResetIDCardID := GetProcAddress(myLibHandle, PChar('ResetIDCardID'));
    @AddIDCardID := GetProcAddress(myLibHandle, PChar('AddIDCardID'));
    @SetIDCardRejectType:=GetProcAddress(myLibHandle,PChar('SetIDCardRejectType'));
    @RecogIDCard := GetProcAddress(myLibHandle, PChar('RecogIDCard'));
    @RecogIDCardEX := GetProcAddress(myLibHandle, PChar('RecogIDCardEX'));
    @GetRecogResult := GetProcAddress(myLibHandle, PChar('GetRecogResult'));
    @GetResultType := GetProcAddress(myLibHandle, PChar('GetResultType'));
    @GetFieldName := GetProcAddress(myLibHandle, PChar('GetFieldName'));
    @GetIDCardName := GetProcAddress(myLibHandle, PChar('GetIDCardName'));
    @GetSubID := GetProcAddress(myLibHandle, PChar('GetSubID'));
	
    @SaveImage := GetProcAddress(myLibHandle, PChar('SaveImage'));
    @SaveHeadImage := GetProcAddress(myLibHandle, PChar('SaveHeadImage'));
	
    @GetVersionInfo := GetProcAddress(myLibHandle, PChar('GetVersionInfo'));
    @GetCurrentDevice := GetProcAddress(myLibHandle, PChar('GetCurrentDevice'));
    @GetDeviceSN := GetProcAddress(myLibHandle, PChar('GetDeviceSN'));
    @CheckDeviceSI := GetProcAddress(myLibHandle, PChar('CheckDeviceSI'));
    @WriteDeviceSI := GetProcAddress(myLibHandle, PChar('WriteDeviceSI'));
	
    @RecogBusinessCard := GetProcAddress(myLibHandle, PChar('RecogBusinessCard'));
    @GetBusinessCardResult := GetProcAddress(myLibHandle, PChar('GetBusinessCardResult'));
    @GetBusinessCardResultCount := GetProcAddress(myLibHandle, PChar('GetBusinessCardResultCount'));
    @GetBusinessCardFieldName := GetProcAddress(myLibHandle, PChar('GetBusinessCardFieldName'));
    @GetBusinessCardPosition := GetProcAddress(myLibHandle, PChar('GetBusinessCardPosition'));
	
    if not Assigned(InitIDCard)
      or not Assigned(FreeIDCard)
      or not Assigned(AcquireImage)
      or not Assigned(SetAcquireImageResolution)
      or not Assigned(SetAcquireImageType)
      or not Assigned(SetUserDefinedImageSize)
      or not Assigned(CheckDeviceOnlineEx)
      or not Assigned(ResetIDCardID)
      or not Assigned(AddIDCardID)
      or not Assigned(SetIDCardRejectType)
      or not Assigned(RecogIDCard)
      or not Assigned(RecogIDCardEx)
      or not Assigned(GetRecogResult)
      or not Assigned(GetResultType)
      or not Assigned(GetFieldName)
      or not Assigned(GetIDCardName)
      or not Assigned(GetSubID)
      or not Assigned(SaveImage)
      or not Assigned(SaveHeadImage)
      or not Assigned(RecogBusinessCard)
      or not Assigned(GetBusinessCardResult)
      or not Assigned(GetBusinessCardResultCount)
      or not Assigned(GetBusinessCardFieldName)
      or not Assigned(GetBusinessCardPosition)
      or not Assigned(GetVersionInfo) 
      or not Assigned(GetCurrentDevice) 
      or not Assigned(GetDeviceSN) 
      or not Assigned(CheckDeviceSI)
      or not Assigned(WriteDeviceSI)then
    begin
      edtTestResult .Text:='Functions export failed -1.'+ #13#10 ;
      Exit;
    end
  end;
  strCode:=UserID.Text; 
  GetMem(pCode, (Length(strCode)+1) * Sizeof(WideChar));
  StringToWideChar(strCode, pCode, (Length(strCode)+1) * Sizeof(WideChar));
  ret:= InitIDCard(pCode, 0, pDllDirectory);
  if ret =0 then
      begin
        edtTestResult.text:='����ʶ����ĳɹ���' ;
        bLoaded:=True;
        end
  else
    begin
          strCode:=IntToStr(ret) ;
          edtTestResult .Text:='����ʶ�����ʧ�ܣ�\r\n����ֵ��'+strCode;
          bLoaded:=False  ;
    end;
   Mutex:=False;
end;


procedure TForm1.BtnSetImageWHClick(Sender: TObject);
var
  strCode:String;
  nWidth:Integer ;
  nHeight:Integer  ;
  bSet:Boolean;
begin
  Mutex:=True;
  strCode:=TBImageWidth.Text;
  if Length(strCode) = 0 then
  begin
    edtTestResult.Text:='�������Զ���ͼ��ߴ���ֵ��';
    Exit;
  end;
  nWidth:=StrToInt(strCode);
  strCode:=TBImageHeight.Text;
  if Length(strCode) = 0 then
  begin
    edtTestResult.Text:='�������Զ���ͼ��ߴ���ֵ��';
    Exit;
  end;
  nHeight:=StrToInt(strCode);
   if bLoaded=False then
      begin
        edtTestResult.Text:='ʶ�����δ�ɹ����أ����ȼ���ʶ�����';
      end
   else
       begin
          if nWidth<0 then
          begin
            edtTestResult.Text:='������������ͼ���ʧ��';
          end;
          if nHeight < 0 then
          begin
            edtTestResult.Text:='������������ͼ���ʧ��';
          end;
          bSet:= SetUserDefinedImageSize (nWidth,nHeight);
          if bSet=True then
          begin
            edtTestResult.Text:='����ͼ���߳ɹ�';
          end
          else
          begin
            edtTestResult.Text:='����ͼ����ʧ��';
          end;
       end;
   Mutex:=False;
end;

procedure TForm1.BtnSetAcquireImgResolutionClick(Sender: TObject);
var
  strCode:String;
  nHoriResolution:Integer ;
  bSet:Boolean;
begin
  Mutex:=True;
  strCode:=TBHoriResolution.Text;
  if Length(strCode)=0then
  begin
    edtTestResult.Text:='�������Զ���ͼ��ֱ�����ֵ';
    Exit;
  end;
  nHoriResolution:=StrToInt(strCode);
   if bLoaded=False then
      begin
        edtTestResult.Text:='ʶ�����δ�ɹ����أ����ȼ���ʶ�����';
      end
   else
       begin
          if nHoriResolution<0 then
          begin
            edtTestResult.Text:='�����������������÷ֱ���';
          end;
          bSet:= SetAcquireImageResolution(nHoriResolution,nHoriResolution);
          if bSet=True then
          begin
            edtTestResult.Text:='����ͼ��ֱ��ʳɹ�';
          end
          else
          begin
            edtTestResult.Text:='����ͼ��ֱ���ʧ��';
          end;
       end;
  Mutex:=False;
end;

procedure TForm1.BtnGetVersionClick(Sender: TObject);
var
  pVerison:PWideChar;
  nSize:Integer;
  nBufferLen:Integer;
  bGetVision:Boolean;
begin
  Mutex:=True;
   if bLoaded=False then
        begin
          edtTestResult.Text:='ʶ�����δ�ɹ����أ����ȼ���ʶ�����';
        end
   else
        begin
           nSize:=128;
           nBufferLen:=50;
           GetMem(pVerison, (128) * Sizeof(WideChar));
           bGetVision:=GetVersionInfo(pVerison,nBufferLen);
           if bGetVision=True then
             begin
                  edtTestResult.Text:=pVerison;
             end
           else
             begin
               edtTestResult.Text:='��ȡ�汾��ʧ��';
             end;  
          
        end;
   Mutex:=False;
end;

procedure TForm1.BtnGetDeviceNameClick(Sender: TObject);
var
  pDevice:PWideChar;
  nSize:Integer;
  nBufferLen:Integer;
  bDevice:Boolean;
begin
  Mutex:=True;
   if bLoaded=False then
        begin
          edtTestResult.Text:='ʶ�����δ�ɹ����أ����ȼ���ʶ�����';
        end
   else
        begin
           nSize:=128;
           nBufferLen:=50;
           GetMem(pDevice, (nSize) * Sizeof(WideChar));
           bDevice:=GetCurrentDevice(pDevice,nBufferLen);
           if bDevice=True then
             begin
                  edtTestResult.Text:=pDevice;
             end
           else
             begin
               edtTestResult.Text:='��ȡ�豸����ʧ��';
             end;  
          
        end;
   Mutex:=False;
end;

procedure TForm1.btnGetDeviceSNClick(Sender: TObject);
var
  lpDeviceSN:PWideChar;
  nSize:Integer;
  nBufferLen:Integer;
  nDevice:Integer;
begin
  Mutex:=True;
   if bLoaded=False then
        begin
          edtTestResult.Text:='ʶ�����δ�ɹ����أ����ȼ���ʶ�����';
        end
   else
        begin
           nSize:=128;
           nBufferLen:=16;
           GetMem(lpDeviceSN, (nSize) * Sizeof(WideChar));
           nDevice:=GetDeviceSN(lpDeviceSN,nBufferLen);
           if nDevice=0 then
             begin
                  edtTestResult.Text:=lpDeviceSN;
             end
           else
             begin
               edtTestResult.Text:='��ȡ�豸���к�ʧ��';
             end;  
          
        end;
   Mutex:=False;
end;

procedure TForm1.btnGetDeviceStatusClick(Sender: TObject);
var
  bDeviceONLine:Boolean;
begin
  Mutex:=True;
  if bLoaded=False then
        begin
          edtTestResult.Text:='ʶ�����δ�ɹ����أ����ȼ���ʶ�����';
        end
   else
    begin
        bDeviceONLine:=CheckDeviceOnlineEx();
       if bDeviceONLine = True then
       begin
         edtTestResult.Text:='�豸����';
       end
       else
         edtTestResult.Text:='�豸������';
    end;
   Mutex:=False;
end;



procedure TForm1.FormClose(Sender: TObject; var Action: TCloseAction);
 begin
   if  bLoaded=True then
   begin
      FreeIDCard();
      bLoaded:=False ;
   end;
    application.Terminate;
 end;


procedure TForm1.btnAcquireImageClick(Sender: TObject);
var
	pPath:PWideChar;
	strPath:String;
  nRet:Integer;
begin
	nRet:=AcquireImage(20);
  if nRet=0 then
  begin
    edtTestResult.Text:='ͼ��ɼ��ɹ���'+ #13#10;
  end
  else
  begin
    edtTestResult.Text:='ͼ��ɼ�ʧ�ܡ�'+ #13#10;
  end;
	strPath:='C:/images/TestUDSize.jpg';
	GetMem(pPath, (Length(strPath)+1) * Sizeof(WideChar));
	StringToWideChar(strPath, pPath, (Length(strPath)+1) * Sizeof(WideChar));
	nRet:=SaveImage(pPath);
  if nRet=0 then
  begin
    edtTestResult.Text:=edtTestResult.Text + 'ͼ�񱣴�ɹ���';
  end
  else
  begin
    edtTestResult.Text:= edtTestResult.Text + 'ͼ�񱣴�ʧ�ܡ����� ' + IntToStr(nRet);
  end;
end;

end.






























