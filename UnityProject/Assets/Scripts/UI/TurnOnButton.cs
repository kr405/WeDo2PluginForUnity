using UnityEngine;

namespace WeDo2Sample
{
    public class TurnOnButton : Button
    {
        [SerializeField] Port m_port;
        [SerializeField] Direction m_direction;
        [SerializeField, Range(0, 100)] byte m_power;

        protected override void OnClick()
        {
            DeviceController.Instance.TurnOnMotor(m_port, m_direction, m_power);
        }
    }
}