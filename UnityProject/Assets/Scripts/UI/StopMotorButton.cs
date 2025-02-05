using UnityEngine;

namespace WeDo2Sample
{
    public class StopMotorButton : Button
    {
        [SerializeField] Port m_port;

        protected override void OnClick()
        {
            DeviceController.Instance.StopMotor(m_port);
        }
    }
}