namespace WeDo2Sample
{
    public class DistanceValueText : ValueText
    {
        void Update()
        {
            UpdateText(DeviceController.Instance.Distance);
        }
    }
}    