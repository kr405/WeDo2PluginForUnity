namespace WeDo2Sample
{
    public class ConnectButton : Button
    {    
        protected override void Awake()
        {
            base.Awake();
            DeviceController.Instance.OnConnectionStatusChanged += UpdateText;
        }
    
        protected override void OnClick()
        {
            if (DeviceController.Instance.IsConnected)
            {
                DeviceController.Instance.Disconnect();
            }
            else
            {
                DeviceController.Instance.Connect();
            }
        }

        /// <summary>
        /// �{�^���̃e�L�X�g���X�V����.
        /// </summary>
        /// <param name="isConnected"></param>
        void UpdateText(bool isConnected)
        {
            Text = isConnected ? "Disconnect" : "Connect";
        }
    }
}
