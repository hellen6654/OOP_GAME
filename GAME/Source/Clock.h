namespace game_framework
{
/////////////////////////////////////////////////////////////////////////////
// �o��class���ѷ|�@���u�����y
// �����N�i�H��g���ۤv���{���F
/////////////////////////////////////////////////////////////////////////////

class Clock
{
    public:
        Clock();
        void LoadBitmap();		// ���J�ϧ�
        void OnMove();			// ����
        void OnShow();			// �N�ϧζK��e��

        int GetX();
        int GetY();
        bool IsFinalBitmap();	//�O���O����̫�@�ibitmap�F
    private:
        int clk_x, clk_y;				// �ϧήy��
        CAnimation clock_animation;	// �Q�ΰʵe�@�ϧ�
};
}