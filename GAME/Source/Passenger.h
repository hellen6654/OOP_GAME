namespace game_framework
{
class Station;
class Passenger
{
    public:
        Passenger();
        Passenger(int, int, int, int, int);
        void LoadBitmap();									//���J�ϧ�
        void SetType(int);
        void SetXY(int, int);
        void SetX(int n);
        void SetY(int n);
        void SetIsNight(bool);
        int GetStartStation();
        int GetFinalStation();
        int GetPassengerType();
        void RandomMadePassenger(vector<Passenger*>& passengerList, vector<Station>& stationList, int stationMaxium, int stationTypeNum, int passenagerNum);
        void OnShow();										//�N�ϧζK��e��
        void RandomOnePassenger(vector<Passenger*>& passengerList, vector<Station>& stationList, int stationMaxium, int stationTypeNum);
        ~Passenger();
    private:
        CMovingBitmap passengerAnimation;					//���ȹϧ�
        CMovingBitmap passengerAnimationNight;					//���ȹϧ�
        int finalStation;									//���I
        int startStation;									//�_�I
        int x, y;											//�ϧήy��
        int passengerType;									//��������
        bool isNight = false;
        //���Ȧb���[����m
        const int PASSENGERPOSITIONX_UPDOWN[6] = { 2, 16, 2, 16, 2, 16 };
        const int PASSENGERPOSITIONY_UPDOWN[6] = { 2, 2, 16, 16, 30, 30 };
        const int PASSENGERPOSITIONX_RIGHTLEFT[6] = { 2, 2, 16, 16, 30, 30 };
        const int PASSENGERPOSITIONY_RIGHTLEFT[6] = { 2, 16, 2, 16, 2, 16 };
        //���Ȧb��������m
        const int PASSENAGE_POSITION[10] = { 25, 36, 47, 58, 69, 80, 91, 102, 113, 124 };
};
}

