namespace WeDo2Sample
{
    public class ScanButton : Button
    {
        protected override void OnClick()
        {
            DeviceController.Instance.Scan();
        }
    }
}