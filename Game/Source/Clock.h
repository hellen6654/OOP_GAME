namespace game_framework
{
////////////////////////////////
//      �o��class���Ѯ���     //
////////////////////////////////

class Clock
{
    public:
        Clock();
        void LoadBitmap();		// ���J�ϧ�
        void OnMove();			// ����
        void OnShow();			// �N�ϧζK��e��

    private:

        int x, y;				// �ϧήy��
        CAnimation animation;	// �Q�ΰʵe�@�ϧ�
};
}