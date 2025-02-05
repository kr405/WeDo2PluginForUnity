namespace WeDo2Sample
{
    public class StopNoteButton : Button
    {
        protected override void OnClick()
        {
            DeviceController.Instance.StopNote();
        }
    }
}