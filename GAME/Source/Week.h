namespace game_framework
{
	

	class Week
	{
	public:
		Week();
		void LoadBitmap();		// ���J�ϧ�
		void OnMove();			// ����
		void OnShow();			// �N�ϧζK��e��
	private:
		int week_x, week_y;				// �ϧήy��
		CAnimation week_animation;
	};
}
