//============================================
//
//	object2D.cpp
//	Author: saito shian
//
//============================================

//============================================
// �C���N���[�h
//============================================
#include <assert.h>
#include "object2D.h"
#include "renderer.h"
#include "object.h"
#include "application.h"
#include "input.h"

//============================================
// �I�u�W�F�N�g�̃R���X�g���N�^
//============================================
CObject2D::CObject2D(int nPriority) : CObject(nPriority)
{
	//============================================
	//�����o�ϐ��̃N���A
	//============================================
	m_pVtxBuff = nullptr;						//�o�b�t�@�̃N���A
	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);		//�ʒu�̃N���A
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ��̃N���A
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//��]�̃N���A
	m_fWidth = 0.0f;							//���̃N���A
	m_fHeight = 0.0f;							//�����̃N���A
	m_fLength = 0;								//�g��k���̃X�P�[���̃N���A
	m_fAngle = 0;								//�p�x�̃N���A
	m_nTimer = 0;								//���Ԃ̃N���A
}

//============================================
// �I�u�W�F�N�g�̃f�X�g���N�^
//============================================
CObject2D::~CObject2D()
{
	//���������Ȃ�
}

//============================================
// �I�u�W�F�N�g(�|���S��)�̏���������
//============================================
HRESULT CObject2D::Init(void)
{
	//============================================
	//�����o�ϐ��̏�����
	//============================================
	m_pVtxBuff = nullptr;														//�o�b�t�@�̏�����
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);										//�ʒu�̏�����
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);										//�ړ��̏�����
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);										//��]�̏�����
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);									//�F�̏�����
	m_size = D3DXVECTOR3(50.0f, 50.0f,0.0f);									//�T�C�Y
	m_fWidth = 25.0f;															//���̏�����
	m_fHeight = 25.0f;															//�����̏�����
	m_fLength = sqrtf(((m_fWidth * m_fWidth) + (m_fHeight * m_fHeight))) / 2;	//�g��k���̃X�P�[���̏�����
	m_fAngle = atan2f(m_fWidth, m_fHeight);										//�p�x�̏�����
	m_nTimer = 0;																//���Ԃ̏�����

	//GetDevive�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/ddd",
		&m_pTexture);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, 0);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, 0);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//============================================
// �I�u�W�F�N�g(�|���S��)�̏I������
//============================================
void CObject2D::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//�j������
	Release();
}

//============================================
// �I�u�W�F�N�g(�|���S��)�̍X�V����
//============================================
void CObject2D::Update(void)
{

}

//============================================
// �I�u�W�F�N�g(�|���S��)�̕`�揈��
//============================================
void CObject2D::Draw(void)
{
	//GetDevive�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,											//���_���̐擪�A�h���X
		2);											//�v���~�e�B�u�̐�

	//�e�N�X�`���̉���
	pDevice->SetTexture(0, NULL);
}

//============================================
// �|���S���̐ݒ菈��
//============================================
void CObject2D::SetPosition(D3DXVECTOR3 pos)
{
	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	m_pos = pos;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
 	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���̍X�V
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, 0);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, 0);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//============================================
// �|���S���̈ړ�
//============================================
void CObject2D::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//============================================
// �|���S���̃T�C�Y�̐ݒ菈��
//============================================
void CObject2D::SetSize(D3DXVECTOR3 size)
{
	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	m_size = size;

	m_fLength = sqrtf(((m_size.x * m_size.x) + (m_size.y * m_size.y))) / 2;	//�g��k���̃X�P�[���̏�����
	m_fAngle = atan2f(m_size.y, m_size.x);									//�p�x�̏�����

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���̍X�V
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, 0);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, 0);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//============================================
// �|���S���̐F�̐ݒ菈��
//============================================
void CObject2D::SetCol(D3DXCOLOR col)
{
	m_col = col;

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(m_col.r, m_col.g, m_col.b, m_col.a);
	pVtx[1].col = D3DXCOLOR(m_col.r, m_col.g, m_col.b, m_col.a);
	pVtx[2].col = D3DXCOLOR(m_col.r, m_col.g, m_col.b, m_col.a);
	pVtx[3].col = D3DXCOLOR(m_col.r, m_col.g, m_col.b, m_col.a);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//============================================
//	��]�̐ݒ�
//============================================
void CObject2D::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;

	m_fLength = sqrtf(((m_size.x * m_size.x) + (m_size.y * m_size.y))) / 2;	//�g��k���̃X�P�[���̏�����
	m_fAngle = atan2f(m_size.y, m_size.x);									//�p�x�̏�����

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z - D3DX_PI + m_fAngle)*m_fLength;
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z - D3DX_PI + m_fAngle)*m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + D3DX_PI - m_fAngle)*m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + D3DX_PI - m_fAngle)*m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z - m_fAngle)*m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z - m_fAngle)*m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + m_fAngle)*m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + m_fAngle)*m_fLength;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//============================================
// �����̐ݒ�
//============================================
void CObject2D::SetLength(float length)
{
	m_fLength = length;

	m_fLength = sqrtf(((m_size.x * m_size.x) + (m_size.y * m_size.y))) / 2;	//�g��k���̃X�P�[���̏�����
	m_fAngle = atan2f(m_size.y, m_size.x);									//�p�x�̏�����

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z - D3DX_PI + m_fAngle)*m_fLength;
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z - D3DX_PI + m_fAngle)*m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + D3DX_PI - m_fAngle)*m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + D3DX_PI - m_fAngle)*m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z - m_fAngle)*m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z - m_fAngle)*m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + m_fAngle)*m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + m_fAngle)*m_fLength;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//============================================
// ����
//============================================
CObject2D *CObject2D::Create(const D3DXVECTOR3 &pos)
{
	CObject2D *pObject2D = nullptr;

	//2D�I�u�W�F�N�g�N���X�̐���
	pObject2D = new CObject2D;				//2D�I�u�W�F�N�g�̃C���X�^���X����

	//null�`�F�b�N
	if (pObject2D != nullptr)
	{
		//����������
		pObject2D->Init();
		//�ݒ菈��
		pObject2D->SetPosition(pos);
	}
	else
	{
		assert(false);
	}
	return pObject2D;
}

//============================================
// �e�N�X�`�����f
//============================================
void CObject2D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

//============================================
// �c�e�N�X�`���摜�̐ݒ�
//============================================
void CObject2D::SetTexture(float SplitX, float nNumIndexX, float SplitY, float nNumIndexY)
{
	//���_���W�ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(nNumIndexX / SplitX, (nNumIndexY) / SplitY);
	pVtx[1].tex = D3DXVECTOR2((nNumIndexX + 1) / SplitX, (nNumIndexY) / SplitY);
	pVtx[2].tex = D3DXVECTOR2(nNumIndexX / SplitX, (nNumIndexY + 1) / SplitY);
	pVtx[3].tex = D3DXVECTOR2((nNumIndexX + 1) / SplitX, (nNumIndexY + 1) / SplitY);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//============================================
// �F�̐ݒ�
//============================================
void CObject2D::SetColor(float Red, float Green, float Blue, float ��)
{
	VERTEX_2D*pVtx;				//���_���ւ̃|�C���^

	m_col = D3DXCOLOR(Red, Green, Blue, ��);

	LPDIRECT3DVERTEXBUFFER9 Buffer = GetBuffer();

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	Buffer->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(Red,Green,Blue,��);
	pVtx[1].col = D3DXCOLOR(Red,Green,Blue,��);
	pVtx[2].col = D3DXCOLOR(Red,Green,Blue,��);
	pVtx[3].col = D3DXCOLOR(Red,Green,Blue,��);

	//���_�o�b�t�@���A�����b�N����
	Buffer->Unlock();
}
