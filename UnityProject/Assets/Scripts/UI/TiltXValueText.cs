namespace WeDo2Sample
{
    public class TiltXValueText : ValueText
    {
        void Update()
        {
            UpdateText(DeviceController.Instance.TiltX);
        }
    }
}

