// TtHideTools.cpp : DLL �̏��������[�`���ł��B
//

#include "stdafx.h"
#include "TtHideTools.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: ���� DLL �� MFC DLL �ɑ΂��ē��I�Ƀ����N�����ꍇ�A
//		MFC ���ŌĂяo����邱�� DLL ����G�N�X�|�[�g���ꂽ�ǂ̊֐���
//		�֐��̍ŏ��ɒǉ������ AFX_MANAGE_STATE �}�N����
//		�����Ȃ���΂Ȃ�܂���B
//
//		��:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �ʏ�֐��̖{�̂͂��̈ʒu�ɂ���܂�
//		}
//
//		���̃}�N�����e�֐��Ɋ܂܂�Ă��邱�ƁAMFC ����
//		�ǂ̌Ăяo�����D�悷�邱�Ƃ͔��ɏd�v�ł��B
//		����͊֐����̍ŏ��̃X�e�[�g�����g�łȂ���΂� 
//		��Ȃ����Ƃ��Ӗ����܂��A�R���X�g���N�^�� MFC
//		DLL ���ւ̌Ăяo�����s���\��������̂ŁA�I�u
//		�W�F�N�g�ϐ��̐錾�����O�łȂ���΂Ȃ�܂���B
//
//		�ڍׂɂ��Ă� MFC �e�N�j�J�� �m�[�g 33 �����
//		58 ���Q�Ƃ��Ă��������B
//

// CTtHideToolsApp

BEGIN_MESSAGE_MAP(CTtHideToolsApp, CWinApp)
END_MESSAGE_MAP()


// CTtHideToolsApp �R���X�g���N�V����

CTtHideToolsApp::CTtHideToolsApp()
: m_ResultString(_T(""))
, m_ResultStringArray()
, m_EditListDialog(NULL)
, m_PatternMatch(NULL)
{
	// TODO: ���̈ʒu�ɍ\�z�p�R�[�h��ǉ����Ă��������B
	// ������ InitInstance ���̏d�v�ȏ��������������ׂċL�q���Ă��������B
}


// �B��� CTtHideToolsApp �I�u�W�F�N�g�ł��B

CTtHideToolsApp theApp;


// CTtHideToolsApp ������

BOOL CTtHideToolsApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

int CTtHideToolsApp::ExitInstance()
{
	if(m_EditListDialog){
		delete m_EditListDialog;
		m_EditListDialog=NULL;
	}
	if(m_PatternMatch){
		delete m_PatternMatch;
		m_PatternMatch=NULL;
	}
	return CWinApp::ExitInstance();
}
