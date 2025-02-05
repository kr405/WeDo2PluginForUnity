using System.Collections;
using TMPro;
using UnityEngine;
using UnityEngine.UI;

namespace WeDo2Sample
{
    public class Notification : TextUI
    {
        Image m_image;
        float m_defaultBgAlpha;
        float m_defaultTextAlpha;
        Coroutine m_coroutine;

        protected override void Awake()
        {
            tMPro = GetComponentInChildren<TextMeshProUGUI>();
            m_image = GetComponent<Image>();
            m_defaultBgAlpha = m_image.color.a;
            m_defaultTextAlpha = tMPro.alpha;
        }

        void Start()
        {
            gameObject.SetActive(false);
        }

        /// <summary>
        /// �A���t�@�l��ݒ肷��.
        /// </summary>
        /// <param name="bgAlpha">�w�i�̃A���t�@�l.</param>
        /// <param name="textAlpha">�e�L�X�g�̃A���t�@�l.</param>
        void SetAlpha(float bgAlpha, float textAlpha)
        {
            var bgColor = m_image.color;
            bgColor.a = bgAlpha;
            m_image.color = bgColor;
            tMPro.alpha = textAlpha;
        }

        /// <summary>
        /// �ʒm���t�F�[�h�A�E�g������.
        /// </summary>
        /// <param name="frames">�t�F�[�h�A�E�g�ɂ�����t���[����.</param>
        /// <param name="delay">�t�F�[�h�J�n�܂ł̎��ԁi�b�j.</param>
        /// <returns></returns>
        IEnumerator FadeOut(int frames, float delay)
        {
            SetAlpha(m_defaultBgAlpha, m_defaultTextAlpha);
            yield return new WaitForSecondsRealtime(delay);

            for (float i = 0; i < frames; i++)
            {
                float t = i / frames;
                SetAlpha(Mathf.Lerp(m_defaultBgAlpha, 0, t), Mathf.Lerp(m_defaultTextAlpha, 0, t));
                yield return null;
            }
            gameObject.SetActive(false);
        }

        /// <summary>
        /// �ʒm��\������.
        /// </summary>
        /// <param name="message">�ʒm���郁�b�Z�[�W.</param>
        public void Notify(string message)
        {
            if (m_coroutine != null)
            {
                StopCoroutine(m_coroutine);
            }
            Text = message;
            gameObject.SetActive(true);
            m_coroutine = StartCoroutine(FadeOut(50, 1));
        }
    }
}