namespace game_framework
{
////////////////////////////////
//     �o��class���ѬP���X    //
////////////////////////////////

class Week
{
    public:
        Week();
        void LoadBitmap();		// ���J�ϧ�
        void OnMove();			// ����
        void OnShow();			// �N�ϧζK��e��
    private:
        int x, y;				// �ϧήy��
        CAnimation animation;	// �Q�ΰʵe�@�ϧ�
};
}